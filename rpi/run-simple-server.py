#!/usr/bin/python

import nrfl
import time

def main():
  time.sleep(1)
  nrfl.setup()

  print("Waiting for NRFL to set ...")
  time.sleep(1)
  while True:
    sender_id = nrfl.NextSenderId()

if __name__ == '__main__':
  main()
