if [ $# -eq 0 ] || [ $1 = "all" ]
then
make -f make_tc.log all
make -f make_tc.log.tests all
elif [ $1 = "clean" ]
then
make -f make_tc.log clean
make -f make_tc.log.tests clean 
else
	echo "Use $0 or $0 all or $0 clean"
fi
