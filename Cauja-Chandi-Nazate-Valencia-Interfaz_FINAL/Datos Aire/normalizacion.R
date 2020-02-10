datos=read.csv("datosA1.csv",header=TRUE,sep= ";")
View(datos)
library(scales)
hum=datos$ï..Humedad=rescale(datos$ï..Humedad,to=c(0,1)) 
pm10n=datos$pm10= rescale(datos$pm10,to=c(0,1)) 
pm2.5n=datos$pm2.5= rescale(datos$pm2.5,to=c(0,1)) 
uvn=datos$uv= rescale(datos$uv,to=c(0,1)) 

library(caTools)
#aleatoriedad de la base de datos, poner al azar conjunto al ntrenamiento y otro a prueba
set.seed(230)
split=sample.split(datos$etiq,SplitRatio = 0.80)
training_set=subset(datos, split==TRUE)
test_set=subset(datos,split==FALSE)
#algoritmo k-NN
library(class)
y_pred=knn(train= training_set[,-5] ,
           test= test_set[-5], 
           cl= training_set[,5], 
           k=15)
#matriz confusion 
cm=table(test_set$etiq,y_pred)
cm

###################clasificador bayesiano############################################
library(e1071)

#convertir a factor la etiqueta 
training_set$etiq=factor(training_set$etiq, levels=c(1,2,3))
#modelo 
class_bayes=naiveBayes(x=training_set[,-5],
                       y=training_set[,5])
#predecir etiqueta
y_pred=predict(class_bayes,newdata=test_set[,-5])
#matriz de confusion
cm=table(test_set$etiq, y_pred)
cm
##knn con CNN ####################
y_pred=knn(train= cnn_training_set[,-5],
           test= test_set[,-5], 
           cl= cnn_training_set[,5], 
           k=1)
#matriz de confusion
cm=table(test_set$etiq, y_pred)
cm
(40)/(80+36)
######################bayes con cnn ####################################
class_bayes=naiveBayes(x=cnn_training_set[,-5],
                       y=cnn_training_set[,5])
#predecir etiqueta
y_pred=predict(class_bayes,newdata=test_set[,-5])
#matriz de confusion
cm=table(test_set$etiq, y_pred)
cm
(40+80)/(36)
###############reducir la base de datos###################################
library(NoiseFiltersR)
drop1_training_set=DROP1(training_set)
#seleccionar solo a los mejores datos
drop1_training_set
#base de datos limpia 
drop1_training_set=drop1_training_set$cleanData

####que variables aportan mayor informacion al clasificador################
library(caret)
set.seed(400)
rPartMod = train(etiq ~ ., data=datos, method="rpart")
rpartImp = varImp(rPartMod,20)
plot(rpartImp, top = 5, main='Variable de mayor importancia')

###########metodo 2 ########################
library(Boruta)
library(mlbench)
library(caret)
library(randomForest)
data("datos")
str(datos)
#Feature selection
set.seed(250)
boruta=Boruta(etiq~ .,data = datos,doTrace=2 , maxRuns=500)
print(boruta)
plot(boruta)
plotImpHistory(boruta)