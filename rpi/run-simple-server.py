#!/usr/bin/python

import nrfl
import time

def main():
  nrfl.setup()
  
  print("Waiting for NRFL to set ...")
  time.sleep(1)
  while True:
    nrfl.loop()

if __name__ == '__main__':
  main()
