case $1 in
	'') echo parametrs not found
	;;
	*[!0-9]*) echo process with pid=$1 wasnt found 
	;;
    *)  if ps -p $1 > /dev/null
    	   	then
      	   	echo -n "Name: " 
			ps -p $1 -o comm=
      	   	echo Pid: $1 
			echo -n "PPid: "$(ps -o ppid= -p $1) 
			echo ''
				if [ "$2" = "fd" ]; then
					for n in $`sudo ls -1 /proc/$1/fd`; do
					echo fd = $n
					done
				fi
      	 fi 
	;;
esac
