f sumHundred( toSum ){

  i = 0;

  sum = 0;
  sumTwo = -1;
  
  while i < 100 {

      sum = sum+toSum;
  
      if sum > 1000 {
      	 sumTwo = 0;
      }
      
  }
  if sumTwo == 0 {
     sum = sumTwo;
  }
  return (sum);
}

sumHundred(1);