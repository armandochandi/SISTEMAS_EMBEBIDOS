datos=read.csv("datosA.csv",header=TRUE,sep= ";")
view(datos)
library(caTools)
set.seed(420)
split=sample.split(datos$etiq,SplitRatio = 0.80)
training_set=subset(datos, split==TRUE)
test_set=subset(datos,split==FALSE)
modelo1<-with(training_set, {glm(etiq~ï..Humedad+pm10+pm2.5+uv)})
summary(modelo1)

modelo2<-with(training_set, {glm(etiq~ï..Humedad+Temp+pm10+uv)})
summary(modelo2)

modelo3<-with(training_set, {glm(etiq~ï..Humedad+Temp+pm10+pm2.5+uv)})
summary(modelo3)

predicciones_entrena=as.factor(ifelse(test = modelo3$fitted.values > 0.26, yes = 1, no = 0))
observaciones_entrena=as.factor(training_set$etiq)

##matriz de confusion###
library(caret)
sub_training_set<-sample_n(training_set, 626)
observaciones_entrena=as.factor(sub_training_set$etiq)
matriz<-confusionMatrix(observaciones_entrena, predicciones_entrena)

