set pagination off

break 7 if (i >= start + 27 * step) && (i <= start + 34 * step)
command 1
        echo @@@
        print start

        echo @@@
        print stop

        echo @@@
        print step

        echo @@@
        print i

        cont
end

run -100 100 3 > /dev/null
quit