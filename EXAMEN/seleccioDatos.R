#Cargar base solo con 2 etiquetas de datos a entorno R
#etiqueta 1: aire puro y etiqueta 2: aire contaminado 
datos=read.csv("datosA1-perceptron.csv",header=TRUE,sep= ";")
view(datos)
library(caTools)
#aleatoriedad para sacar conjunto de prueba y conjunto de entrenamiento
set.seed(377)
split=sample.split(datos$etiq,SplitRatio = 0.80)
entrenamiento=subset(datos, split==TRUE)
prueba=subset(datos,split==FALSE)

#importancia de variables
library(data.table)
library(Boruta)
summary(datos)

#importancia de los atributos
boruta.model=Boruta(etiq~., data = datos, doTrace = 2)
getSelectedAttributes(boruta.model, withTentative = F)

#ranking de atributos
x <- attStats(boruta.model)
ranking <- data.table(attribute=rownames(x), x)[order(-meanImp)]
print(ranking)