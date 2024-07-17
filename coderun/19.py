import sys


def main():

    s = input().strip()
    s = s.replace('|', ' | ')
    s = s.replace('&', ' & ')
    s = s.replace('^', ' ^ ')
    s = s.replace('!', ' ~ ')
    s = '(' + s + ')'
    res = eval(f'{s}')
    if res == 1:
        print(1)
    else:
        print(0)


if __name__ == '__main__':
    main()