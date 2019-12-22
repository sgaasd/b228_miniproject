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

void drive(const /* noget med miniproject*/ & msg){
    geometry_msgs::Twist cmd_vel_message;
    ros::Rate loop_rate(21);
    int Safety = /* msg_tpe fra miniproject */;
    if (ros::ok && Safety!=0 && Safety!=1 && Safety!=2){  
        for(int i=0; i<=42; i++){
        cmd_vel_pub.publish(DriveMsg(0.0, 0.2));
        loop_rate.sleep();
        }
    }else if (Safety==0 || Safety==1){
        for(int i=0; i<=42; i++){ 
            cmd_vel_pub.publish(DriveMsg(-0.2, 0.0));
            loop_rate.sleep();
        }
        for(int i=0; i<=42; i++){ 
            cmd_vel_pub.publish(DriveMsg(0.0, -(0.75)));
            loop_rate.sleep();
        }
    }
    else if (Safety==2){
        for(int i=0; i<=42; i++){ 
            cmd_vel_pub.publish(DriveMsg(-0.2, 0.0));
            loop_rate.sleep();
        }
        for(int i=0; i<=42; i++){
            cmd_vel_pub.publish(DriveMsg(0.0, (0.75)));
            loop_rate.sleep();
        }
    }    
}



/* Her er ændringen til dig San*/