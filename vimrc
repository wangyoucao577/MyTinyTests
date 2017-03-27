

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" vi compatible
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set nocompatible    " vi compatible off



""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" spaces, tabs, line numbers
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set expandtab       " tabs are spaces
set tabstop=4       " number of visual spaces per TAB
set softtabstop=4   " numbre of spaces in tab when editing
set shiftwidth=4    
set number          " show line numbers



""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" syntax, highlights, line and column cursor, colors
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set t_Co=256        " vim support 256 colors

syntax enable       " enable syntax highlight
set background=dark
" highlight current line and column
au WinLeave * set nocursorline nocursorcolumn
au WinEnter * set cursorline cursorcolumn
set cursorline cursorcolumn
set showmatch       " highlight matching [{()}]

"let g:solarized_termcolors=256
"colorscheme solarized

"colorscheme wombat
"colorscheme desert256v2
"colorscheme molokai

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" search
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set incsearch       " search as characters are entered
set hlsearch        " hignlight matches
set ignorecase      " ignore case when search
set smartcase       " when searching try to be smart about cases



""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" misc.
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set showcmd         " show command in the bottom bar
set wildmenu        " visual autocomplete for command menu
set lazyredraw      " redraw only when we need to
set ruler           " always show current position (line, column)
set history=1000    " how many lines of history VIM has to remember



""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" auto save, file encoding
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set autowrite       " auto save

set fileencodings=utf-8,euc-cn,cp936,utf-16,big5 "try decode file with these charactors
set encoding=utf-8  " deal with files with this charactors




