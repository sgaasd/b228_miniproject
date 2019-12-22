#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

void drive(/*parametre fra safety*/);

ros::Publisher cmd_vel_pub;

geometry_msgs::Twist DriveMsg(float x, float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = z;
    cmd_vel_message.linear.x = x;
    return cmd_vel_message;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Drive");

    ros::NodeHandle n;

    ros::Subscriber miniproject_sub = n.subscribe("miniproject", 1, drive);

    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
     
    ros::spin();

    return 0;
}

void drive(/*parametre fra safety*/){
    geometry_msgs::Twist cmd_vel_message;
    ros::Rate loop_rate(21);
    if (ros::ok && Safety==false){  
        for(int i=0; i<=42; i++){
        cmd_vel_pub.publish(DriveMsg(0.0, 0.2));
        loop_rate.sleep();
        }
    } else if (Safety==true){
        /*for(int i=0; i<=42; i++){
        cmd_vel_pub.publish(DriveMsg(0.0, -0.2));
        loop_rate.sleep();
        }
        for(int i=0; i<=42; i++){
        cmd_vel_pub.publish(DriveMsg(0.2, 0.0));
        loop_rate.sleep();
        }
        */
       switch (/*safety parameter*/){
                    /*If the sensor on the left side is pressed the robot 
                    will first drive backwards and turn right*/
                    case 0:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(DriveMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(DriveMsg(0.0, -(0.75)));
                        loop_rate.sleep();
                    }
                    break;
                    /*If the sensor on the middle is activated the robot 
                    will drive backwards and turn left*/
                    case 1:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(DriveMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){
                        cmd_vel_pub.publish(DriveMsg(0.0, (0.75)));
                        loop_rate.sleep();
                    }
                    break;
                    /*If the sensor on the right side is pressed the robot 
                    will drive backwards and turn left*/
                     case 2:
                    for(int i=0; i<=42; i++){ 
                        cmd_vel_pub.publish(DriveMsg(-0.2, 0.0));
                        loop_rate.sleep();
                    }
                    for(int i=0; i<=42; i++){
                        cmd_vel_pub.publish(DriveMsg(0.0, (0.75)));
                        loop_rate.sleep();
                    }
                    break;
                }
    }

}