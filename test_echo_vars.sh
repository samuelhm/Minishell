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

tmux send-keys -t my_session:0.0 'echo $USER' C-m
tmux send-keys -t my_session:0.1 'echo $USER' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'echo "$USER"' C-m
tmux send-keys -t my_session:0.1 'echo "$USER"' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 "echo '\$USER'" C-m
tmux send-keys -t my_session:0.1 "echo '\$USER'" C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'echo $USER/Hello' C-m
tmux send-keys -t my_session:0.1 'echo $USER/Hello' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'echo -n hola' C-m
tmux send-keys -t my_session:0.1 'echo -n hola' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'echo -nnnnnn hola' C-m
tmux send-keys -t my_session:0.1 'echo -nnnnnn hola' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'echo -n -nn -nnn hola' C-m
tmux send-keys -t my_session:0.1 'echo -n -nn -nnn hola' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'echo -na hola' C-m
tmux send-keys -t my_session:0.1 'echo -na hola' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'echo -n -na hola' C-m
tmux send-keys -t my_session:0.1 'echo -n -na hola' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'export fd4=/home' C-m
tmux send-keys -t my_session:0.1 'export fd4=/home' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'cd /' C-m
tmux send-keys -t my_session:0.1 'cd /' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'pwd' C-m
tmux send-keys -t my_session:0.1 'pwd' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'cd $fd4' C-m
tmux send-keys -t my_session:0.1 'cd $fd4' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'pwd' C-m
tmux send-keys -t my_session:0.1 'pwd' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'cd $fd4/$USER' C-m
tmux send-keys -t my_session:0.1 'cd $fd4/$USER' C-m
sleep 0.05
tmux send-keys -t my_session:0.0 'pwd' C-m
tmux send-keys -t my_session:0.1 'pwd' C-m

tmux send-keys -t my_session:0.0 "echo \"\'\'\'\"" C-m
tmux send-keys -t my_session:0.1 "echo \"\'\'\'\"" C-m
sleep 0.05
tmux send-keys -t my_session:0.0 "echo \"'''\"" C-m
tmux send-keys -t my_session:0.1 "echo \"'''\"" C-m
sleep 0.05
tmux send-keys -t my_session:0.0 "echo '\"\"\"'" C-m
tmux send-keys -t my_session:0.1 "echo '\"\"\"'" C-m
# Sincroniza los paneles para que ambos reciban las mismas entradas
tmux setw synchronize-panes on

# Adjunta la sesión de tmux para que la puedas ver en la terminal
tmux attach-session -t my_session


