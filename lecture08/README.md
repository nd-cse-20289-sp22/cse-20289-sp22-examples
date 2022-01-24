# Examples 08

# Pipeline: Powerful Pattern

Three volunteers to role-play and demonstrate a pipeline.

1. How many Starbursts are pink?

        read | filter pink | count

2. How many different colors of Starbursts do we have?

        read | sort | uniq

# Pipeline: Demonstration

1. How many instances of bash are running?

        $ ps aux | grep bash | grep -v grep | wc -l

2. How many different types of shells are being used?

        $ ps aux | grep -Ev '(grep|ssh|flush)' | grep -Eo '(bash|zsh)' | sort | uniq

    To see how many of each, do `uniq -c`

3. Who has the most processes?

        for user in $(ps aux | cut -d ' ' -f 1 | sort | uniq); do
            echo $(ps aux | grep -v grep | grep ^$user | wc -l) $user
        done | sort -rn

    Alternatively:

        ps aux | cut -d ' ' -f 1 | sort | uniq -c | sort -rn

4. Who has the most TROLL/sleep processes?

        ps aux | grep TROLL | cut -d ' ' -f 1 | sort | uniq -c | sort -rn

# Regular Expressions: Syntax

        $ echo "Matthew" | grep -E '.*'             # Match all letters

        $ echo "Matthew" | grep -E 't*'             # Match zero or more t's

        $ echo "Nicole"  | grep -E 'e?'             # Match zero or one e's

        $ echo "Nicolee" | grep -E 'e{2}'           # Match exactly 2 e's

        $ echo "Nicolee" | grep -E '[eio]*'         # Match all i, o, e's

        $ echo "Nicolee" | grep -E '[eio]+'         # Match one or more of i, o, e's

        $ echo "Nicolee" | grep -E '[^eio]+'        # Match everything but E or A

        $ echo "Nicolee" | grep -E '^N'             # Match start

        $ echo "Nicolee" | grep -E 'e$'             # Match end

        $ echo "Nicolei" | grep -E '(i).*\1'          # Match with group references

# Regular Expressions: Examples

1. All the strings                                      .*

2. Only charmander and chespin                          ^[ch]

3. All words with two t's                               t{2}

4. Words that don't start with a vowel                  ^[^aeiou]

5. All words with two consecutive vowels                [aeiou]t

6. All words with two consecutive letters (same)        (.)\1

7. All words that begin and end with the same letter    ^([a-z]).*\1$

8. All words with exactly 2 of r, s, or t               '^[^rst]*[rst][^rst]*[rst][^rst]*$'

# Activity: Contact Harvesting

1. Extract all the phone numbers

        $ curl -sL https://yld.me/d51B | grep -Eo '[0-9]{3}-[0-9]{3}-[0-9]{4}' | sort

2. Extract all the email addresses

        $ curl -sL https://yld.me/d51B | grep -Eo '[[:alnum:]]+@[[:alnum:]\.]+' | sort | uniq

3. Extract all the "Assistant" positions

        $ curl -sL "http://yld.me/d51B"| grep -Eo '[^>]*+Assistant[^<]*' | sort

# Activity: CSE Curriculum

1. How many MATH vs PHYS vs CSE courses?

        $ curl -sL https://yld.me/zlH | grep -Eo '(MATH|PHYS|CSE)' | sort | uniq -c

2. How many credits per semester?

        $ curl -sL https://yld.me/zlH
		| sed -En 's/.*Total Credit Hours: ([0-9]{2}|[0-9]{2}\.[0-9]).*/\1/p'
		| sort | uniq -c

3. How many sophomore CSE courses?

        $ curl -sL https://yld.me/zlH | grep -Eo 'CSE 2[0-9]{4}' | sort

        $ curl -sL https://yld.me/zlH
		| sed 's/<br>/\n/g' | sed -En 's/.*(CSE 2[0-9]{4}).*/\1/p' | sort

4. How many sophomore CSE credits?

        $ curl -sL https://yld.me/zlH
		| sed 's/<br>/\n/g' 
		| sed -En 's/.*(CSE 2[0-9]{4}).*([0-9]) credits.*/\2/p'
		| awk '{ sum += $1 } END { print sum }'

5. How many different types of electives?

        $ curl -sL https://yld.me/zlH
		| sed -E 's/<(br|p)>/\n/g' 
		| grep -v meta
		| sed -En 's/([^>]+ Elective).*credits.*/\1/p' 
		| sort | uniq -c
