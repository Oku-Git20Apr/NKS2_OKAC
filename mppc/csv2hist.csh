#!/usr/bin/csh -f

set file1 = $1
set file2 = $2

if ( $file1 == "" ) then
    echo "usage: "
    echo " csv2hist.csh [csv file name] [hist file name]"
    echo ""
    exit
endif
if ( $file2 == "" ) then
    echo "usage: "
    echo " csv2hist.csh [csv file name] [hist file name]"
    echo ""
    exit
endif

set flag = "false"
set counter = 0 

echo "# csv to hist converted" > $file2

foreach line ( `cat $file1 | tr "<>" " "` )
	if ( $line == "DATA" ) then
        set flag = "true"
    endif

    if ( $flag == "true" ) then
        if ( $line != "DATA" ) then
            if ( $line != "END" ) then
                echo $counter $line >> $file2
                @  counter++
            endif
        endif
    endif

end

