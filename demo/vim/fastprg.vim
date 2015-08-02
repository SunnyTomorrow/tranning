map<C-H> :call SetTitle()<CR>
map<C-F> :call SetFuncNote()<CR>

function SetTitle()
    if &filetype == "cpp" || &filetype == "h" || &filetype == "hpp" || &filetype == "cc"
        call append(line(".") + 0,"/*******************************************")
        call append(line(".") + 1,"*")
        call append(line(".") + 2,"*@file: ".expand("%:t"))
        call append(line(".") + 3,"*")
        call append(line(".") + 4,"*@brief: ")
        call append(line(".") + 5,"*")
        call append(line(".") + 6,"*@author: huang jun")
        call append(line(".") + 7,"*")
        call append(line(".") + 8,"*@date: ".strftime("%Y-%m-%d"))
        call append(line(".") + 9,"*")
        call append(line(".") + 10,"*@history: ")
        call append(line(".") + 11,"*")
        call append(line(".") + 12,"********************************************/")
        call append(line(".") + 13,"")
        if expand("%:e") == "h" || expand("%:e") == "hpp"
            call append(line(".") + 14,"#ifndef _".toupper(expand("%:t:r"))."_H_")
            call append(line(".") + 15,"#define _".toupper(expand("%:t:r"))."_H_")
            call append(line(".") + 16,"")
            call append(line(".") + 17,"#endif //_".toupper(expand("%:t:r"))."_H_")
            call append(line(".") + 18,"")
            call cursor(line(".") + 17,0)
        else
            call cursor(line(".") + 14,0)
        endif
    endif 
endfunction

function SetFuncNote()
    if &filetype == "cpp" || &filetype == "h" || &filetype == "hpp" || &filetype == "cc"
        call append(line(".") + 0,"/****@function:")
        call append(line(".") + 1,"@input: ")
        call append(line(".") + 2,"@ouput: ")
        call append(line(".") + 3,"@return: ")
        call append(line(".") + 4,"@brief: ")
        call append(line(".") + 5,"*****/")
    endif
endfunction
