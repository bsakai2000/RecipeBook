#!/usr/bin/env bash

# The path to our binary
recipeBookPath="recipeBook"

_recipeBook()
{
	case ${#COMP_WORDS[@]} in
		# If we have 1, something is wrong. Give up
		1 ) ;;
		# If we have 2, give our first level menu options
		2 )
			COMPREPLY=($(compgen -W "add list recipe search" "${COMP_WORDS[1]}"))
			;;
		# If we have 3, give second level menu options based on first level menu
		3 )
			case "${COMP_WORDS[1]}" in
				"list" )
					COMPREPLY=($(compgen -W "ingredients recipes tags" "${COMP_WORDS[2]}"))
					;;
				"recipe" )
					COMPREPLY=($(compgen -W "all ingredients instructions notes" "${COMP_WORDS[2]}"))
					;;
				"search" )
					COMPREPLY=($(compgen -W "ingredient tag" "${COMP_WORDS[2]}"))
					;;
			esac
			;;
		# Past 3, we are assuming this is a search
		* )
			unescaped=()
			# Decide which submenu we're in
			case "${COMP_WORDS[1]}" in
				"recipe" )
					# If we're looking at a recipe, create our list from the list of recipes
					if [[ $COMP_CWORD -eq 3 && "${COMP_WORDS[2]}" =~ ^(all|ingredients|instructions|notes)$ ]]
					then
						local IFS=$'\n'
						wordlist="$($recipeBookPath list recipes)"
						wordlist="${wordlist/\'/\\\'}"
						unescaped=($(compgen -W "$wordlist" "${COMP_WORDS[3]}"))
					fi
					;;
				"search" )
					case "${COMP_WORDS[2]}" in
						# If we're looking for a recipe, make our list from the list of ingredients
						"ingredient" )
							local IFS=$'\n'
							wordlist="$($recipeBookPath list ingredients)"
							wordlist="${wordlist/\'/\\\'}"
							unescaped=($(compgen -W "$wordlist" "${COMP_WORDS[COMP_CWORD]}"))
							;;
						# If we're looking for a tag, make our list from the list of tags
						"tag" )
							local IFS=$'\n'
							wordlist="$($recipeBookPath list tags)"
							wordlist="${wordlist/\'/\\\'}"
							unescaped=($(compgen -W "$wordlist" "${COMP_WORDS[COMP_CWORD]}"))
							;;
					esac
					;;
			esac

			# Format for output
			if [ ${#unescaped[@]} -eq 0 ]
			then
				COMPREPLY=()
			else
				# If we're not quoted, we need to escape certain characters
				if [[ ${COMP_WORDS[COMP_CWORD]} == \"* ]]
				then
					COMPREPLY=("${unescaped[@]}")
				else
					COMPREPLY=($(printf '%q\n' "${unescaped[@]}"))
				fi
			fi
	esac
}

complete -F _recipeBook $recipeBookPath
