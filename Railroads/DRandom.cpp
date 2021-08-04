#include <dmainscreen.h>
#include <QDateTime>

void DMainScreen::Randomize()
{

      seed = QDateTime::currentMSecsSinceEpoch()%ULONG_MAX;

      for (int i=0;i<32;i++)
          LFSR[i]=(seed>>i)%2;

      for (int i=0;i<32;i++)
          CAR_1[i]= LFSR[31-i];
      //init LFSR state


}


uint XNOR(uint a, uint b)
{
    return a==b?1:0;
}

uint XOR(uint a, uint b)
{
    return a==b?0:1;
}

unsigned long long DMainScreen::DRandom()
{

//32 22 2 1

   uint temp[32];

   for (int i=0;i<32;i++)
       temp[i]=LFSR[i];

   for (int i=1;i<32;i++)
       LFSR[i]=temp[i-1];
   LFSR[0] = XNOR(XNOR(XNOR(temp[31],temp[21]),temp[1]),temp[0]);


   for (uint counts = 0; counts < (seed%64); counts++){

   for (int i=0;i<32;i++)
       temp[i]=CAR_1[i];
}

    for (uint i=0;i<32;i++)
        {
            uint left,right;

            left = i-1; right = i+1;
            if (i==0)
                {left = 31;right =1;}
            if (i==31)
                {left = 30; right = 0;}

            uint config = ((temp[left]%2)<<2) + ((temp[i]%2)<<1) + (temp[right]%2);

            switch (config)
            {
                case 0:
                    CAR_1[i] = 0;
                break;
            case 1:
                    CAR_1[i] = 1;
            break;
            case 2:
                    CAR_1[i] = 0;
            break;
            case 3:
                    CAR_1[i] = 1;
            break;
            case 4:
                    CAR_1[i] = 1;
            break;
            case 5:
                    CAR_1[i] = 0;
            break;
            case 6:
                    CAR_1[i] = 1;
            break;
            case 7:
                    CAR_1[i] = 0;
            break;
            default:
            break;
            }



        }






   unsigned long long total = 0;

   for (int i=0;i<32;i++)
       {
  //  total += (XNOR(LFSR[i],CAR_1[i])<<i);
             total += (XOR(LFSR[i],CAR_1[i])<<i);

       }

   seed = total;

   return total;

}


