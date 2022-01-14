#!/bin/sh

PATH=~pbui/pub/pkgsrc/bin:$PATH
COWFILE=tux

prompt_question() {
    shuf <<EOF | head -n 1 | cowsay -f $COWFILE
Hello ${USER}, what question do you have for me today?
Hi ${USER}, what can I do for you?
Why ${USER}, what is on your mind?
Ah ${USER}! What brings you to me?
EOF
}

answer_question() {
    shuf <<EOF | head -n 1 | cowsay -f $COWFILE
It is certain
It is decidedly so
Without a doubt
Yes, definitely
You may rely on it
As I see it, yes
Most likely
Outlook good
Yes
Signs point to yes
Reply hazy try again
Ask again later
Better not tell you now
Cannot predict now
Concentrate and ask again
Don't count on it
My reply is no
My sources say no
Outlook not so good
Very doubtful
EOF
}

early_exit() {
    shuf <<EOF | head -n 1 | cowsay -f $COWFILE
Leaving so soon?
Au revoir.
Adios.
Fine, be that way.
You didn't really want to know anyways.
EOF
    exit 1
}

trap early_exit HUP INT TERM

prompt_question
QUESTION=""
while [ -z "$QUESTION" ]; do
    read -p "Question? " QUESTION
done
answer_question

# vim: set sts=4 sw=4 ts=8 ft=sh:
