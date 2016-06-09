for file in test_hfst.py examples.py test.py; do
    if python3 $file > /dev/null 2> /dev/null; then
        echo $file" passed" 
    else
        echo $file" failed" 
    fi
done

for n in 2 3 5 7 9; do
    if python3 test$n.py > /dev/null 2> /dev/null; then
        echo "test"$n".py passed" 
    else
        echo "test"$n".py failed" 
    fi
done

#if (cat foobar.hfst foobar2.hfst | python3 test4.py > /dev/null 2> /dev/null); then
#    echo "test4.py passed" 
#else
#    echo "test4.py failed" 
#fi

echo "skipping test4.py"
echo "skipping test8.py"

