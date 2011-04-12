y = ones(1,100);
y(1) = 100;
%exGain = 1 ;
%inGain = 0.5;
%z=zeros(1,100);
k = 1;
%gr = 0.0009;

%fs = 200;
%t = 0 : (1/fs) : 100;
%f = 50;
%exGain = sin(2 * pi * f .* t);

%for m = 1:100

for j=1:6000
    exGain(j) = random('unif',0,1); 
    inGain(j) = random('unif',0,1);
end


%MODEST IS 0.000009 and 0.00000009

%AGRESSIVE IS 0.00009; and 0.000009;

kEx = 0.00009;
kIn = 0.000009;

    rndfoodtgr1 = random('unif', 0, 3000); % to trigger food anytime befoer four minutes:
    rndfoodtgr2 = random('unif', 3001, 5750);
figure(1);    
for i=2:6000
    exG = exGain(i) * y(i-1) * kEx;
    inG = inGain(i) * y(i-1) * kIn;
    kLv = 0;%y(i-1) * 0.00001;
    
    %y(i) = y(i-1) * exp(( - inG - kLv) * k);
    
    % if i<3000 || i>3250 
    
    if i>rndfoodtgr1 && i< rndfoodtgr1+250 
        
        y(i) = y(i-1) * exp((exG - kLv) * k); 
        
    elseif i>rndfoodtgr2 && i< rndfoodtgr2+250 
        
        y(i) = y(i-1) * exp((exG - kLv) * k); 
        
    else
        y(i) = y(i-1) * exp(( - inG - kLv) * k);
        
    end
end


plot(1:6000,y);
% mean(y)
drawnow;
%z(m) = mean (y);

%end
disp(z);