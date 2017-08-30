
import argparse


def main():

    parser = argparse.ArgumentParser(description='test for python cmd argparse module, maybe also optional getopt module.')
    
    # default positional arguments
    parser.add_argument('square', help='display a square of a given number', type=int)

    # `-*` or `--*` means optional arguments
    #parser.add_argument('--echo', help='echo the string you use enter') # require follow content unless set one by action
    
    # cannot both exist by `add_mutually_exclusive_group`
    verbose_group = parser.add_mutually_exclusive_group()
    verbose_group.add_argument('-v', '--verbose', action='count', default=0, help='display verbose log') 
    verbose_group.add_argument('-q', '--quiet', action='store_true', help='display less log') 
    #parser.add_argument('-v', '--verbose', action='count', default=0, help='display verbose log') 
    
    args = parser.parse_args()
        
    if args.square:
        answer = args.square ** 2

        if args.verbose >= 2:   # `-vv`
            print "the square of {} equals {}".format(args.square, answer)
        elif args.verbose == 1: # `-v`
            print "{}^2 == {}".format(args.square, answer)
        else:
            print answer



if __name__ == '__main__':
    main()


