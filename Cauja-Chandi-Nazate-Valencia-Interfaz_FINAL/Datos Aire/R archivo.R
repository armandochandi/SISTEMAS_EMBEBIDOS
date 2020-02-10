#Cargar base de datos a entorno R
datos=read.csv("datosA.csv",header=TRUE,sep= ";")
view(datos)
library(caTools)
#aleatoriedad de la base de datos, poner al azar conjunto al ntrenamiento y otro a prueba
set.seed(325)
split=sample.split(datos$etiq,SplitRatio = 0.80)
training_set=subset(datos, split==TRUE)
test_set=subset(datos,split==FALSE)

#algoritmo k-NN
library(class)
y_pred=knn(train= training_set[,-6] ,
           test= test_set[-6], 
           cl= training_set[,6], 
           k=15)
#matriz confusion 
cm=table(test_set$etiq,y_pred)
cm
((22+19+36)/(22+19+36))*100
###################clasificador bayesiano############################################
library(e1071)

#convertir a factor la etiqueta 
training_set$etiq=factor(training_set$etiq, levels=c(1,2,3))
#modelo 
class_bayes=naiveBayes(x=training_set[,-6],
                       y=training_set[,6])
#predecir etiqueta
y_pred=predict(class_bayes,newdata=test_set[,-6])
#matriz de confusion
cm=table(test_set$etiq, y_pred)
cm
###############reducir la base de datos###################################
library(NoiseFiltersR)
cnn_training_set=DROP3(training_set)
#seleccionar solo a los mejores datos
cnn_training_set
#base de datos limpia 
cnn_training_set=cnn_training_set$cleanData

##########################knn con cnn###############################
y_pred=knn(train= cnn_training_set[,-6],
           test= test_set[,-6], 
           cl= cnn_training_set[,6], 
           k=3)
#matriz de confusion
cm=table(test_set$etiq, y_pred)
cm
######################bayes con cnn ####################################
class_bayes=naiveBayes(x=cnn_training_set[,-6],
                       y=cnn_training_set[,6])
#predecir etiqueta
y_pred=predict(class_bayes,newdata=test_set[,-6])
#matriz de confusion
cm=table(test_set$etiq, y_pred)
cm