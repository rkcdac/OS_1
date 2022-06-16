#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int press_data = 0;
pthread_rwlock_t rwlock;

void *serial(void *data)
{
    while(1)
    {

    printf("Serial  : asking for lock \n");
   
    pthread_rwlock_rdlock(&rwlock);

    printf("Serial : got lock\n");
    sleep(5);
    printf("Serial: pressure data :%d\n",press_data);
    
    pthread_rwlock_unlock(&rwlock);

    printf("Serial :Unlock\n");
    
    }

}


void *ether(void *data)
{
    while(1)
    {
    sleep(10);
    printf("Ether :asking lock\n");

    pthread_rwlock_rdlock(&rwlock);
    printf("Ether : got lock\n");

    printf("Ether:Pressure data : %d\n",press_data );


    pthread_rwlock_unlock(&rwlock);
    printf("Ether :Unlock\n");


    }


    

}



void*calibrate(void *data)
{

while(1)
{
sleep(2);
printf("Cal :asking for lock\n");

pthread_rwlock_wrlock(&rwlock);
printf("calibrate :got lock\n");
press_data ++;
printf("Calibrate :Pressur data:%d\n",press_data);
pthread_rwlock_unlock(&rwlock);
printf("Calibrate :Unlock\n");


}
    

}


int main(int argc, char const *argv[])
{
    
pthread_t sid,eid,cid;

pthread_rwlock_init(&rwlock,NULL);

pthread_create(&sid,NULL,serial,NULL);
pthread_create(&eid,NULL,ether,NULL);
pthread_create(&cid,NULL,calibrate,NULL);


pthread_join(sid,NULL);
pthread_join(eid,NULL);
pthread_join(cid,NULL);


pthread_rwlock_destroy(&rwlock);


    return 0;
}
