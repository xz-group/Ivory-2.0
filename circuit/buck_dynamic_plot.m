clear
hFig = figure;



X = load('model_all.txt'); 
t1 = X(:,1).*1e6;
v1 = X(:,2);
plot(t1,v1,'LineWidth',1.5,'Color',[159,0,19]./255);
hold on



X = load('buck_1_all.txt'); 
t2 = X(:,1).*1e6;
v2 = X(:,2);
plot(t2,v2,'LineWidth',1.5,'Color',[35,190,54]./255);
hold on


X = load('buck_10_all.txt'); 
t3 = X(:,1).*1e6;
v3 = X(:,2);
plot(t3,v3,'LineWidth',1.5,'Color',[36,3,86]./255);
hold on

set(gca, 'fontname', 'Arial');
set(gca, 'fontsize', 12);
set(gca, 'linewidth',1);
set(gca,'FontWeight','bold');
y1 = ylabel({'Voltage(V)'});
x1 = xlabel({'Time(us)'});
grid on;
grid minor;
axis([0 40 0.4 1.2])

legend('{Buck IVR switch free average model}','1-phase buck IVR(SPICE)','10-phase buck IVR(SPICE)')
%gridLegend(hdlY,2);