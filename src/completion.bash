#!/usr/bin/env bash

# The path to our binary
recipeBookPath="./recipeBook"

recipe_completions()
{
	case ${#COMP_WORDS[@]} in
		# If we have 1, something is wrong. Give up
		1 ) ;;
		# If we have 2, give our first level menu options
		2 )
			COMPREPLY=($(compgen -W "list recipe search" "${COMP_WORDS[1]}"))
			;;
		# If we have 3, give second level menu options based on first level menu
		3 )
			case "${COMP_WORDS[1]}" in
				"list" )
					COMPREPLY=($(compgen -W "ingredients recipes tags" "${COMP_WORDS[2]}"))
					;;
				"recipe" )
					COMPREPLY=($(compgen -W "all ingredients instructions" "${COMP_WORDS[2]}"))
					;;
				"search" )
					COMPREPLY=($(compgen -W "ingredient tag" "${COMP_WORDS[2]}"))
					;;
			esac
			;;
		# Past 3, we are assuming this is a search
		* )
			case "${COMP_WORDS[1]}" in
				"recipe" )
					if [[ COMP_CWORD -eq 3 && "${COMP_WORDS[2]}" =~ ^(all|ingredients|instructions)$ ]]
					then
						local IFS=$'\n'
						unescaped=($(compgen -W "$($recipeBookPath list recipes)" "${COMP_WORDS[3]}"))
						COMPREPLY=($(printf '%q\n' "${unescaped[@]}"))
					fi
					;;
				"search" )
					case "${COMP_WORDS[2]}" in
						"ingredient" )
							local IFS=$'\n'
							unescaped=($(compgen -W "$($recipeBookPath list ingredients)" "${COMP_WORDS[COMP_CWORD]}"))
							COMPREPLY=($(printf '%q\n' "${unescaped[@]}"))
							;;
						"tag" )
							local IFS=$'\n'
							unescaped=($(compgen -W "$($recipeBookPath list tags)" "${COMP_WORDS[COMP_CWORD]}"))
							COMPREPLY=($(printf '%q\n' "${unescaped[@]}"))
							;;
					esac
					;;
			esac
	esac
}

complete -F recipe_completions $recipeBookPath
