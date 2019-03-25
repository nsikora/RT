while (( "$#" )); do
	./rt maps/$1.json &
	sleep 1
	shift
done
