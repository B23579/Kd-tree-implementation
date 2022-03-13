library(tidyverse)
library(tibble)
library(data.table)


result<-read.csv("reslopenmp.csv.txt", header = FALSE,sep=";") 
result%>%rename(Thread_number=V1, n=V2, walltime=V3)-> result
result$Thread_number<- as.integer(result$Thread_number)
result$n <- as.integer(result$n)
result$walltime <- as.numeric(result$walltime) 

view(result)
# strong Scaling :
#1- Fixe the problem size
#2- measure how solution time decrease with more processor 

re<-result
re$walltime<-as.numeric(re$walltime)/60

re$n <-as.factor(re$n)
p<-ggplot(data=re)+
  geom_line(mapping = aes(Thread_number,walltime, color=n))+
  geom_point(mapping = aes(Thread_number,walltime, color=n))+
  labs(x="Number of thread", y= "Runtime (min)", title = "Strong scalability")+
  theme(plot.title = element_text(hjust = 0.3))
p
ggsave(p, filename = "strongscalability.png")


# weak scaling 

# 1- fixe the problem size per core, 
#2- measure if the solution time remain unchange with large problem(more processor)
re<-result
re$walltime<-as.numeric(re$walltime)/60
re$Thread_number<- as.factor(as.integer(re$Thread_number))


p<-ggplot(data=re)+
  geom_line(mapping = aes(n,walltime, color=Thread_number))+
  geom_point(mapping = aes(n,walltime, color=Thread_number))+
  labs(x="Number of thread", y= "Runtime (min)", title = "Strong scalability")+
  theme(plot.title = element_text(hjust = 0.3))
p

ggsave(p, filename = "weakscaling.png")



# speed up
# since we was unable to get the time execution for n=9 using 1 thread,
# we will discard the problem size 9

result<-filter(result, n!=9)
view(result)
resu<-filter(result, result$Thread_number==1)
resu1<-filter(result, result$Thread_number==5)
resu2<-filter(result, result$Thread_number==10)
resu3<-filter(result, result$Thread_number==16)
resu4<-filter(result, result$Thread_number==20)
rsul<-filter(result, result$Thread_number==24)
rsul1<-filter(result, result$Thread_number==34)
rsul2<-filter(result, result$Thread_number==48)

# speed-up
resu<-mutate(resu,speed=resu$walltime/resu$walltime)
resu1<-mutate(resu1,speed=resu$walltime/resu1$walltime)
resu2<-mutate(resu2,speed=resu$walltime/resu2$walltime)
resu3<-mutate(resu3,speed=resu$walltime/resu3$walltime)
resu4<-mutate(resu4,speed=resu$walltime/resu4$walltime)
rsul<-mutate(rsul,speed=resu$walltime/rsul$walltime)
rsul1<-mutate(rsul1,speed=resu$walltime/rsul1$walltime)
rsul2<-mutate(rsul2,speed=resu$walltime/rsul2$walltime)


# efficiency 

resu<-mutate(resu,Efficiency=resu$speed/resu$Thread_number)
resu1<-mutate(resu1,Efficiency=resu$speed/resu1$Thread_number)
resu2<-mutate(resu2,Efficiency=resu$speed/resu2$Thread_number)
resu3<-mutate(resu3,Efficiency=resu$speed/resu3$Thread_number)
resu4<-mutate(resu4,Efficiency=resu$speed/resu4$Thread_number)
rsul<-mutate(rsul,Efficiency=rsul$speed/rsul$Thread_number)
rsul1<-mutate(rsul1,Efficiency=rsul1$speed/rsul1$Thread_number)
rsul2<-mutate(rsul2,Efficiency=rsul2$speed/rsul2$Thread_number)

total <- rbind(resu,resu1,resu2,resu3,resu4, rsul,rsul1,rsul2)

view(total)

total$Thread_number <-as.numeric(total$Thread_number)
total$n <-as.factor(total$n)
p<-ggplot(data=total)+
  geom_line(mapping = aes(Thread_number,speed, color=n))+
  geom_point(mapping = aes(Thread_number,speed, color=n))+
  labs(x="Number of thread", y= "speed-up", title = "Speedup using openmp")+
  theme(plot.title = element_text(hjust = 0.3))
p
ggsave(p,filename = "speedupopenmp.png")


total1<-total
##### 
total$n<-as.numeric(as.character(total1$n))
total<-filter(total,Thread_number>1)
total$n <-as.factor(total$n)


p<-ggplot(data=total)+
  geom_line(mapping = aes(Thread_number,Efficiency, color=n))+
  geom_point(mapping = aes(Thread_number,Efficiency, color=n))+
  labs(x="Number of thread", y= "Efficiency", title = "Efficiency using openmp")+
  theme(plot.title = element_text(hjust = 0.3))

p
ggsave(p,filename = "efficientypopenmp.png")

l<-filter(result,result$n==4)
p<-ggplot(data=l)+
  geom_line(mapping = aes(Thread_number,walltime))+
  geom_point(mapping = aes(Thread_number,walltime))+
  labs(x="Number of thread", y= "Runtime(s)", title = "Strong scalbility for n=4")+
  theme(plot.title = element_text(hjust = 0.3))

p 
ggsave(p,filename = "strongscalabilityfor_4.png")
fwrite(total, "total.csv")


total$n<-as.integer(as.character(total$n))
weak<-filter(total,total$Thread_number==5,n==4)%>%
  rbind(filter(total,total$Thread_number==10,total$n==5))%>%
  rbind(filter(total,total$Thread_number==20,total$n==6))%>%
  rbind(filter(total,total$Thread_number==34,total$n==7))%>%
  rbind(filter(total,total$Thread_number==48,total$n==8))
  
view(weak)

# weak scalability 
weak1<- weak
weak$n <- as.factor(weak$n)

p<-ggplot(data=weak)+
  geom_line(mapping = aes(Thread_number,walltime))+
  geom_point(mapping = aes(Thread_number,walltime,color=n))+
  labs(x="Number of thread", y= "Runtime(s)", title = "Weak scalbility")+
  theme(plot.title = element_text(hjust = 0.3))

p 
ggsave(p,filename = "weakscalability.png")

p<-ggplot(data=weak)+
  geom_line(mapping = aes(Thread_number,speed))+
  geom_point(mapping = aes(Thread_number,speed,color=n))+
  labs(x="Number of thread", y= "Speedup", title = "Weak Speedup")+
  theme(plot.title = element_text(hjust = 0.3))

p 
ggsave(p,filename = "weak speedup.png")

