function int max(int a,int b)
{
  if(a>b)
  {
    return a;
  }
  else
  {
    return b;
  }
}

function int main() {
  int result = 1;
  int i = 2;
  int n;
  input n;
  
  while (i <= n) {
    result = result * i;
    i++;
  }

  for(int j=0;j<9;j++)
      result=result*i;

  if(i!=n+1)
  {
    output "123\n";
  }
  else
  {
    output "456\n";
  }
  
  output "result=";
  output result;
  output "\n";
  output "aaaaa\n";
  int a;
  input a;
  output "max(i,a)=";
  int k=max(i,a);
  output k;
  output "\n";
}