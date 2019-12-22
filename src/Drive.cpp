#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <b228_miniproject/safety_msg.h>

void drive(const b228_miniproject::safety_msg::ConstPtr& msg);

int PreCount = 0;
int Safety = 0;
int Count = 0;

ros::Publisher cmd_vel_pub;

geometry_msgs::Twist DriveMsg(float x, float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = z;
    cmd_vel_message.linear.x = x;
    return cmd_vel_message;
}

void safetyAction(int SideHit){
    switch (SideHit)
        {
        case 0:
            std::cout << "Drej til højre0" << std::endl;
            break;

        case 1:
            std::cout << "Drej til højre1" << std::endl;
            break;

        case 2:
            std::cout << "Drej til venstre2" << std::endl;
            break;
        
        default:
            std::cout << "Something went wrong" << std::endl;
            break;
        }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Drive");

    ros::NodeHandle n;

    ros::Subscriber miniproject_sub = n.subscribe("/miniproject/safety", 1, drive);

    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
    
    while (ros::ok)
    {
        geometry_msgs::Twist cmd_vel_message;
        if (PreCount != Count)
        {
            safetyAction(Safety);
            PreCount = Count;
        } else {
            cmd_vel_pub.publish(DriveMsg(0.0, 0.2));
        }
        ros::spinOnce();
    }
    
/*
    geometry_msgs::Twist cmd_vel_message;
    if (PreCount != Count)
    {
        safetyAction(Safety);
        PreCount = Count;
    } else {
        cmd_vel_pub.publish(DriveMsg(0.0, 0.2));
    }
*/
    ros::spin();

    return 0;
}


void drive(const b228_miniproject::safety_msg::ConstPtr& msg){
    //geometry_msgs::Twist cmd_vel_message;
    //ros::Rate loop_rate(21);
    std::cout << "drive funktion aktiveret" << std::endl;

    Safety = msg->side;
    Count++;

    /*
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
    } */   
}



/* Her er ændringen til dig San*/