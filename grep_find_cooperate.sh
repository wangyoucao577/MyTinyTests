
echo "Begin find..."

C_FILES=`find . -name '*.c'`
echo "Find Result:"
echo $C_FILES

echo "Find Done, start grep..."
grep -i -n 'main' $C_FILES 
