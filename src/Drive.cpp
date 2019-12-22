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

    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);

    //Kald på Drive 
     
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
        for(int i=0; i<=42; i++){
        cmd_vel_pub.publish(DriveMsg(0.0, -0.2));
        loop_rate.sleep();
        }
        for(int i=0; i<=42; i++){
        cmd_vel_pub.publish(DriveMsg(0.2, 0.0));
        loop_rate.sleep();
        }
    }

}