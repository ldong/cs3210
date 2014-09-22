
" Vundle -------------------------------------------------------------
set nocompatible                " get out of vi-compatible mode
filetype off                    " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" let Vundle manage Vundle, required
Plugin 'gmarik/Vundle.vim'

" languages
Plugin 'tpope/vim-commentary'
"Plugin 'scrooloose/syntastic'
"Plugin 'scrooloose/nerdcommenter'
"Plugin 'vim-scripts/vimwiki'
"Plugin 'xolox/vim-notes'
" Plugin 'smancill/conky-syntax.vim'

" text manipulation
Plugin 'tpope/vim-surround'
" Plugin 'tpope/vim-repeat'
" Plugin 'godlygeek/tabular'

" colors
Plugin 'chriskempson/base16-vim'
" Plugin 'bling/vim-airline'
Plugin 'itchyny/lightline.vim'
Plugin 'lilydjwg/colorizer'

" navigation
Plugin 'jeffkreeftmeijer/vim-numbertoggle'
" Plugin 'tpope/vim-vinegar'
Plugin 'scrooloose/nerdtree'

" other utilities
Plugin 'xolox/vim-misc'
" Plugin 'tpope/vim-dispatch'
" Plugin 'tpope/vim-fugitive'
" Plugin 'tpope/vim-unimpaired'

call vundle#end()       " required
syntax on
filetype plugin on      " required
filetype indent on      " required


" vim-airline settings -----------------------------------------------
" let g:airline_theme = 'ubaryd'
" let g:airline_left_sep=''
" let g:airline_left_alt_sep='|'
" let g:airline_right_sep=''
" let g:airline_right_alt_sep='|'
" let g:airline_section_z=''
" let g:airline#extensions#tabline#left_sep = ' '
" let g:airline#extensions#tabline#left_alt_sep = '|'
" let g:airline#extensions#tabline#right_sep = ' '
" let g:airline#extensions#tabline#right_alt_sep = '|'
" let g:airline#extensions#tabline#enabled = 1
" function! AirlineInit()
"   let g:airline_section_a = airline#section#create(['mode','branch'])
"   let g:airline_section_b = airline#section#create_left(['%f%m'])
"   let g:airline_section_c = airline#section#create(['filetype'])
"   let g:airline_section_x = airline#section#create(['ffenc'])
"   " let g:airline_section_y = airline#section#create(['%B'])
"   let g:airline_section_z = airline#section#create_right(['%p%%','L: %l','C: %c'])
" endfunction
" autocmd VimEnter * call AirlineInit()


" lightline settings -------------------------------------------------
let g:Powerline_symbols = 'fancy'
let g:lightline = {
  \ 'colorscheme': 'wombat',
  \ }


" General ------------------------------------------------------------
set encoding=utf-8
set clipboard=unnamed           " share windows clipboard += windows
set fileformat=unix
set fileformats=unix,dos
"set nobinary

autocmd BufNewFile,BufReadPost *.md set filetype=markdown
autocmd BufNewFile,BufRead *.md setlocal spell spelllang=en_us


" Colors -------------------------------------------------------------
set t_Co=256                    " force 256 colors
let base16colorspace=256        " access colors present in 256 colorspace
colorscheme base16-ashes
set background=dark

let g:rehash256=1
" let g:sh_indent_case_labels=1

" overwrite base16-vim setting for transparent background
highlight Normal ctermbg=NONE


" Relocate annoying files --------------------------------------------
set undodir=~/.vim/undo//
set backupdir=~/.vim/backup//
set directory=~/.vim/swap//
set viminfo+=n~/.vim/.viminfo
set undofile                    " enable persistent undo
set backup                      " create backup files
set undolevels=1000             " max number of changes that can be undone
set undoreload=10000            " max number of lines to save for undo on buffer reload


" Look and feel ------------------------------------------------------
set autoread                    " set to auto read when file changed from the outside
set number                      " show line numbers
set relativenumber              " use relative line numbers
set nowrap                      " disable wrapping
set mouse=c                     " disable mouse in normal/insert/command/visual
set ttyfast                     " improve scrolling speed
set nofoldenable                " disable folding
set noerrorbells                " disable bell/flash
set history=1000                " command history length
set hidden                      " don't fucking whine about unsaved buffers

set scrolloff=15                " keep 15 lines vertical for scope
set sidescrolloff=5             " keep 5 lines horizontal at the side
set sidescroll=1                " number of columns to scroll at a time
set backspace=2                 " make backspace work normally
set tabpagemax=15               " max 15 tabs open
set laststatus=2                " always display statusbar
set previewheight=20            " maximum height for preview window
set showmatch                   " highlight matching brackets
set matchtime=5                 " tenths of a second to blink matching brackets

set hlsearch                    " highlight all search matches
set incsearch                   " start search highlighting before hitting 'enter'
set ignorecase                  " perform case-insensitive search
set smartcase                   " ...unless search term has a capital letter
set gdefault                    " s///g by default

set linespace=0                 " line padding
set nostartofline               " leave cursor where it was
set report=0                    " report back all changes
set ruler                       " always show current positions along the bottom
set omnifunc=ccomplete#Complete " we use C god damnit

set cursorline
set colorcolumn=80              " use column highlighting instead of word-wrap

set listchars=trail:·,tab:▸\
" set listchars=trail:·,tab:▸\ ,eol:¬,extends:»,precedes:«,conceal:†,nbsp:␣
set list

" set statusline=%F\ %y\ [%{&ff}]\ %m%r%h%w     " full Filepath, filetype, fileformat, mod
" set statusline+=%=                            " rw, help, preview
" set statusline+=[L:\ %l/%L]\ [C:\ %v]\ [%p%%] " line number, column number, percent

set showcmd     " show command on last line of screen (as they're being input)
set showmode

" visual autocomplete for command menu
set wildmenu
set completeopt=menu,menuone,longest,preview

" gVimdisable menubar, toolbar, etc
" set guioptions-=T
" set guioptions-=e
" set guioptions-=r
" set guioptions-=m
" set guifont=Terminus\ 12

set splitright                  " split windows to right
set splitbelow                  " split windows to bottom


" Tab behavior -------------------------------------------------------
set autoindent                  " set cursor at same indent
set smartindent                 " autoindent
set smarttab        " testing, new command
set expandtab                   " use spaces instead of tabs
set shiftwidth=2                " tab width = 2 spaces
set tabstop=2                   " spaces for <Tab>
set softtabstop=2               " spaces for editng, e.g. <Tab> or <BS>


" Keybindings --------------------------------------------------------
set pastetoggle=<F2>            " F2 to toggle paste mode
let mapleader = "\<Space>"

" re-wrap paragraphs
nnoremap <leader>q gqip

" Re-indent file, keeping cursor position
map <leader>= mzgg=G`z<CR>

" remove all trailing whitespaces
nnoremap <leader>W :%s/\s\+$//<cr>:let @/=''<cr>

" :W! to write to a file using sudo
cmap W! %!sudo tee > /dev/null %

" Copy & paste to system clipboard with <Space>p and <Space>y
vmap <Leader>y "+y
vmap <Leader>d "+d
nmap <Leader>p "+p
nmap <Leader>P "+P
vmap <Leader>p "+p
vmap <Leader>P "+P

" quick (v)split
nnoremap <silent> ss :split<CR>
nnoremap <silent> vv :vsplit<CR>

" move between windows with CTL + {h,j,k,l}
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l

" switch buffers with K and L
noremap K :bp<CR>
noremap L :bn<CR>

" open a new empty buffer
nmap <Leader>b :enew<CR>

" close current buffer and move to previous one
nmap <Leader>bq :bp <BAR> bd #<CR>

" show all open buffers and their status
nmap <Leader>bl :ls<CR>

" Jump to start and end of line using [F]ront and [R]ear
noremap F ^
noremap R $

" move up/down on a wrapped line with k and l
nnoremap k gj
nnoremap l gk

" do things right / turn off arrow keys
nnoremap <up> <nop>
nnoremap <down> <nop>
nnoremap <left> <nop>
nnoremap <right> <nop>
inoremap <up> <nop>
inoremap <down> <nop>
inoremap <left> <nop>
inoremap <right> <nop>

" clear search highlight with <space><space>
nnoremap <leader><space> :noh<cr>

" Use sane/perl-like regular expressions
nnoremap / /\v
vnoremap / /\v

" move around code blocks with <TAB>
nnoremap <tab> %
vnoremap <tab> %

" no one ever hits F1 on purpose
inoremap <F1> <ESC>
nnoremap <F1> <ESC>
vnoremap <F1> <ESC>

" switch to normal mode with jj
inoremap jj <ESC>

" remap to normal home keys
noremap j h
noremap k j
noremap l k
noremap ; l


" Functions -------------------------------------------------
" Prevent replacing paste buffer on paste
function! RestoreRegister()
  let @" = s:restore_reg
  return ''
endfunction
function! s:Repl()
  let s:restore_reg = @"
  return "p@=RestoreRegister()\<cr>"
endfunction
vmap <silent> <expr> p <sid>Repl()

