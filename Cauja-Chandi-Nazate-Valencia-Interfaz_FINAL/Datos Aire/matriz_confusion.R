datos=read.csv("datosA.csv",header=TRUE,sep= ";")
view(datos)
####EVALUACION DE MODELOS DE CLASIFICACION#####################
####INSTALANDO LIBRERIAS ISLR MASS dplyr############################
nrow(datos)
ntrain <- nrow(datos)*0.8
ntest <- nrow(datos)*0.2
c(ntrain,ntest).
library(ISLR)
library(MASS)
library(dplyr)
set.seed(325)
index_train<-sample(1:nrow(datos),size = ntrain)
train<-datos[index_train,]
test<-datos[-index_train,]
summary(train)
summary(test)
logit_reg <- glm(etiq~.,data=train)
lda_fit<-lda(etiq~.,data=train)

predicted_value <- predict(logit_reg,test,type = "response")
predicted_class <- ifelse(predicted_value>0.5, "Yes","No")
performance_data<-data.frame(observed=test$etiq,
                             predicted= predicted_class)

positive <- sum(performance_data$observed=="Yes")
negative <- sum(performance_data$observed=="No")
predicted_positive <- sum(performance_data$predicted=="Yes")
predicted_negative <- sum(performance_data$predicted=="No")
total <- nrow(performance_data)
data.frame(positive, negative,predicted_positive,predicted_negative)