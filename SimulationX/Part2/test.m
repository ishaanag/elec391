

coordinateX = 200;
coordinateY = 0;

r = sqrt(coordinateX^2+coordinateY^2);
theta_d = atand(coordinateY/coordinateX);

theta_one = acosd(r/200)+ theta_d;
theta_two = 2*theta_d-theta_one;

theta_one = theta_one*-3;
theta_two = theta_two*-3;

y = [theta_one;theta_two];

theta_one = theta_one/-3;
theta_two = theta_two/-3;

coordinateX = 100*cosd(theta_one) + 100*cosd(theta_two);
coordinateY = 100*sind(theta_one) + 100*sind(theta_two);


% Return Default Result
z = [coordinateX;coordinateY];