#==================================================================================
#								MANDATORY_TEST
#==================================================================================


valgrind --trace-children=yes --leak-check=full --track-fds=yes --show-leak-kinds=all

./pipex infile cat "wc -l" outfile
env -i ./pipex infile cat "wc -l" outfile
env -i ./pipex infile ewvrefv "wc -l" outfile
env -i ./pipex infile cat errvjoi outfile
./pipex infile qweffe "wc -l" outfile
./pipex infile /bin/cat "wc -l" outfile
./pipex infile cat "/bin/wc -l" outfile
./pipex infile /bin/wrfrqe "wc -l" outfile
./pipex infile cat /qewd/wc outfile
./pipex nofile cat "wc -l" outfile
./pipex nofile saDAS "wc -l" outfile




#unset PATH
#/usr/bin/valgrind

./pipex infile /bin/cat "/bin/wc -w" outfile
./pipex infile /bin/qwef "/bin/wc -w" outfile

export PATH=/mnt/nfs/homes/amahla/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

#===================================================================================
#								BONUS_TEST
#===================================================================================

./pipex infile cat cat cat cat cat cat cat cat cat outfile

./pipex here_doc LOL cat cat cat cat cat cat cat cat cat outfile
./pipex here_doc LOL cat cat cat ewgw cat cat cat cat cat outfile
