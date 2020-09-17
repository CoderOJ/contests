while true; do
    ./D-data > tmp.in 
    ./D     < tmp.in > tmp1.out 
    ./D-std < tmp.in > tmp2.out 
    if diff tmp1.out tmp2.out; then 
        printf "AC\n"  
 
    elif diff -B -b tmp1.out tmp2.out; then
        printf "PE\n"
 
    else
        printf "WA\n" 
        exit 0
    fi
done

