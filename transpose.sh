echo "Enter number of rows:"
read r
echo "Enter number of columns:"
read c

echo "Enter matrix elements:"
for ((i=0;i<r;i++))
do
     read -a row
  for ((j=0;j<c;j++))
  do
     a[$((i*c+j))]=${row[j]}
  done
done

echo "Transpose of matrix:"
for ((i=0;i<c;i++))
do
  for ((j=0;j<r;j++))
  do
   
    val=${a[$((j*c+i))]}
        echo -n "$val"
  done

done
