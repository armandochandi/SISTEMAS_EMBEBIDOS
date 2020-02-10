######curvas roc y auc#####################
datos=read.csv("datosA.csv",header=TRUE,sep= ";")
view(datos)
str(datos)
library(nnet)
mymodel=multinom(etiq~.,data=datos)

p=predict(mymodel,datos)
tab=table(p,datos$ï..Humedad)
tab
1-sum(diag(tab))/sum(tab)
table(datos$etiq)

library(ROCR)
pred=predict(mymodel,datos,type='prob')
pred=prediction(pred,datos$etiq)
eval=performance(pred,"acc")
plot(eval)

##########identificar los mejores valors
max=which.max(slot(eval,"y.values")[[1]])