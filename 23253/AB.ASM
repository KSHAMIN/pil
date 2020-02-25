.model small
.code
                mov dl,41h    ;saving 'A' for printing purpose
                mov ah,02h    ;02h for character output
                int 21h       ;interrupt 21h for random read

                mov dl,42h    ;saving 'B' for printing purpose
                mov ah,02h    
                int 21h

                mov ah,04ch   ;04ch to terminate program
                int 21h

                end
