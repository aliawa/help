# .bashrc

# if not running interactively, don't do anything
[ -z "$PS1" ] && return

# get local settings
[ -f ~/.bash_local ] && source ~/.bash_local

# bash_sensible from https://github.com/mrzool/bash-sensible.git
[ -f ~/.sensible.bash ] && source ~/.sensible.bash

# Local path
export PATH=$PATH:~/bin:~/pan_bin


# set vim as default editor
export EDITOR=vim
export TERM="xterm-256color"


# alias 
case "$OSTYPE" in
     darwin*)  
            alias ls='ls -G'
            alias ll='ls -oFGh'
            alias la='ls -AoFGh'
            alias ldir='ls -odFGh */'
            alias l.='ls -dG .*'
            alias latest='CLICOLOR_FORCE=yes ls -oFGht | head'
            ;;
      linux*) 
            alias ls='ls --color=auto'
            alias ll='ls -l --color=auto'
            alias ldir='ls --color=auto -dl */'
            alias l.='ls -lad .[^.]*'
            alias latest='ls -l -F -t | head'
            if [[ -e /usr/bin/vimx ]]; then 
                alias vi='vimx'
            else 
                alias vi='vim'
            fi
            alias minicom='sudo minicom -m -c on'
            alias grep='grep --color=auto'
            if [ -f ~/.dircolors-solarized/dircolors.ansi-dark ]; then
                eval `dircolors ~/.dircolors-solarized/dircolors.ansi-dark`
            fi
            ;;
      cygwin) ;; # Windows
        bsd*) ;; # BSD
           *) ;; # Unknown
esac



# make ls sort files with dot files first
export LC_COLLATE=C


# Colored man pages (see man 5 terminfo)
# mb -- begin blinking
# md -- begin bold
# me -- end mode
# se -- end standout-mode
# ue -- end underline
# us -- begin underline
# so -- standout statusbar/search -> magenta
man() {
    env \
        LESS_TERMCAP_md=$'\E[00;38;5;73m'  \
        LESS_TERMCAP_me=$'\E[0m'           \
        LESS_TERMCAP_se=$'\E[0m'           \
        LESS_TERMCAP_ue=$'\E[0m'           \
        LESS_TERMCAP_us=$'\E[04;38;5;146m' \
        LESS_TERMCAP_so=$'\E[01;35;47m'    \
        man "$@"
}


# git completion
[ -f ~/bin/git-completion.bash ] && . ~/bin/git-completion.bash

export PS1=$'\[\e[35;40m\]\u\[\e[m\]\[\e[40m\]@\[\e[m\]\[\e[33;40m\]\h\[\e[m\]\[\e[40m\]:\[\e[m\]\[\e[32;40m\]\w\[\e[m\] \u00bb '


# Fix tmux DISPLAY env variable
if [ -n "$DISPLAY" ]; then
    for name in `tmux ls 2> /dev/null | sed 's/:.*//'`; do
        tmux setenv -g -t $name DISPLAY $DISPLAY
    done
fi

# disable terminal flow control (Ctrl-S, Ctrl-Q)
stty -ixon


# fuzzy finder
[ -f ~/.fzf.bash ] && source ~/.fzf.bash
# export FZF_DEFAULT_COMMAND='fd --type f'
export FZF_DEFAULT_COMMAND='if [ -f gtags.files ]; then cat gtags.files; else fd --type f; fi' 
export FZF_CTRL_T_COMMAND="$FZF_DEFAULT_COMMAND"
_fzf_compgen_path() {
  fd --hidden --follow --exclude ".git" . "$1"
}
_fzf_compgen_dir() {
  fd --type d --hidden --follow --exclude ".git" . "$1"
}


