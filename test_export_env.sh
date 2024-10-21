#!/bin/bash

# Inicia una nueva sesión de tmux llamada "my_session"
tmux new-session -d -s my_session

# Divide la ventana en dos paneles (uno a la izquierda y otro a la derecha)
tmux split-window -h
tmux send-keys -t my_session:0.0 'bash' C-m
tmux send-keys -t my_session:0.1 'make' C-m
tmux send-keys -t my_session:0.1 './minishell' C-m
tmux send-keys -t my_session:0.0 'clear' C-m
tmux send-keys -t my_session:0.1 'clear' C-m

tmux send-keys -t my_session:0.1 'unset LS_COLORS' C-m
tmux send-keys -t my_session:0.0 'unset LS_COLORS' C-m

sleep 0.05
tmux send-keys -t my_session:0.0 'export a b c' C-m
tmux send-keys -t my_session:0.1 'export a b c' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'export | grep "declare -x a"' C-m
tmux send-keys -t my_session:0.1 'export | grep "declare -x a"' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'export | grep "declare -x b"' C-m
tmux send-keys -t my_session:0.1 'export | grep "declare -x b"' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'export | grep "declare -x c"' C-m
tmux send-keys -t my_session:0.1 'export | grep "declare -x c"' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'env | grep "a="' C-m
tmux send-keys -t my_session:0.1 'env | grep "a="' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'env | grep "b="' C-m
tmux send-keys -t my_session:0.1 'env | grep "b="' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'env | grep "c="' C-m
tmux send-keys -t my_session:0.1 'env | grep "c="' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'unset a b c ' C-m
tmux send-keys -t my_session:0.1 'unset a b c ' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'unset a b c ' C-m
tmux send-keys -t my_session:0.1 'unset a b c ' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'export | grep "declare -x a"' C-m
tmux send-keys -t my_session:0.1 'export | grep "declare -x a"' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'export | grep "declare -x b"' C-m
tmux send-keys -t my_session:0.1 'export | grep "declare -x b"' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'export | grep "declare -x c"' C-m
tmux send-keys -t my_session:0.1 'export | grep "declare -x c"' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'env | grep "a="' C-m
tmux send-keys -t my_session:0.1 'env | grep "a="' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'env | grep "b="' C-m
tmux send-keys -t my_session:0.1 'env | grep "b="' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'env | grep "c="' C-m
tmux send-keys -t my_session:0.1 'env | grep "c="' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'export a=hola b='\''hola'\'' "c= hola"' C-m
tmux send-keys -t my_session:0.1 'export a=hola b="hola" "c= hola"' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'export | grep "declare -x a"' C-m
tmux send-keys -t my_session:0.1 'export | grep "declare -x a"' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'export | grep "declare -x b"' C-m
tmux send-keys -t my_session:0.1 'export | grep "declare -x b"' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'export | grep "declare -x c"' C-m
tmux send-keys -t my_session:0.1 'export | grep "declare -x c"' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'env | grep "a="' C-m
tmux send-keys -t my_session:0.1 'env | grep "a="' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'env | grep "b="' C-m
tmux send-keys -t my_session:0.1 'env | grep "b="' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'env | grep "c="' C-m
tmux send-keys -t my_session:0.1 'env | grep "c="' C-m
# Sincroniza los paneles para que ambos reciban las mismas entradas
tmux setw synchronize-panes on

# Adjunta la sesión de tmux para que la puedas ver en la terminal
tmux attach-session -t my_session


