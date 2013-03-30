#!/usr/bin/python

import nrfl

def main():
  nrfl.setup()
  while True:
    nrfl.loop()

if __name__ == '__main__':
  main()
