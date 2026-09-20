import argparse
import random

parser = argparse.ArgumentParser()
parser.add_argument('--n', type=int, help='length of generated sequence')
parser.add_argument('--max_elem', type=int, help='max element of generated sequence')
parser.add_argument('--min_elem', type=int, default=0, help='min element of generated sequence')

args = parser.parse_args()

if args.n <= 0:
    raise ValueError(f'invalid length of sequence {args.n}')

if args.min_elem > args.max_elem:
    raise ValueError(f'min element ({args.min_elem}) can\'t be greater than max element ({args.max_elem})')

with open('./data/input.txt', 'w') as f:
    f.write(f'{args.n}\n')
    for _ in range(args.n):
        f.write(f'{random.randint(args.min_elem, args.max_elem)} ')
