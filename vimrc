set nocompatible
filetype plugin indent on

set nu
set ai
set showcmd
set expandtab
set tabstop=4
set softtabstop=4
set shiftwidth=4
set t_Co=256
colo torte

function CP_R( fileinput )
    let fn = expand("%")
    let fn_wo_exp = expand("%:r")
	
	if( &ft == 'cpp') 
		let cpl = 'g++ -w -o "' . fn_wo_exp . '" -std=c++11 "' . fn . '"' | let exc = '"./' . fn_wo_exp . '"'
	elseif( &ft == 'c')
		let cpl = 'gcc -w -o "' . fn_wo_exp . '" "' . fn . '"' | let exc = '"./' . fn_wo_exp . '"'
	elseif( &ft == 'java')
		let cpl = 'javac "' . fn . '"' | let exc = 'java "' . fn_wo_exp . '"'
	elseif( &ft == 'python')
		let exc = 'python3 "' . fn . '"'
	endif

	let pause = 'printf "Press any key to continue..." && read -n 1 && exit'
	if !exists('exc')
		echo 'Can''t compile or run this file...'
		return
	endif

    " optional
    if a:fileinput
        call inputsave()
        let inputfile = input('Input file: ')
        let outputfile = input('Output file: ')
        call inputrestore()
        if inputfile != ''
            let exc = exc . ' < "' . inputfile . '"'
        endif
        if outputfile != ''
            let exc = exc . ' > "' . outputfile . '"'
        endif
    endif
	
    if exists('cpl')
		let cp_r = cpl . ' && time ' . exc
	else
		let cp_r = 'time ' . exc
    endif
    " change gnome-terminal to other if needed
	silent execute '!gnome-terminal -x bash -c ''' . cp_r . ';' . pause . ''''
    redraw!
endfunction

map <F9> :w<CR>:call CP_R(0)<CR><ESC>
map <C-F9> :w<CR>:call CP_R(1)<CR><ESC>
map <F10> :%y+<CR>
