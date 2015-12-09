if [ $# -eq 0 ] || [ $1 = "all" ]
then
make -f make_tc.common all
make -f make_tc.common.tests all
elif [ $1 = "clean" ]
then
make -f make_tc.common clean
make -f make_tc.common.tests clean 
else
	echo "Use $0 or $0 all or $0 clean"
fi
