// *** Author: Group B228    *** //
// *** Project: Mini project *** //
// *** Node: Drive node      *** //
// *** Created: 31-12-2019   *** //

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <b228_miniproject/safety_msg.h>

#include <stdlib.h>
#include <time.h>

/*A prototype of the Drive function is made*/
void drive(const b228_miniproject::safety_msg::ConstPtr& msg);

/*Variables for counting, and the safety functions is declared and initialized*/
int PreCount = 0;
int Count = 0;
int Sidehit = 0;

/*A ros publisher is declared*/
ros::Publisher cmd_vel_pub;

/*A function for returning Geometry_msgs::Twist variables is made
    This function helps shorten the overall code.*/
geometry_msgs::Twist DriveMsg(float x, float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = z;
    cmd_vel_message.linear.x = x;
    return cmd_vel_message;
}

/*A function for calling when a safety action should be executet is declared.*/
void safetyAction(int SideHit){
    srand (time(NULL));
    int Turns = rand() % 50 + 10;

    ros::Rate loop_rate(20);
    switch (SideHit)
        {
            /*If a sensor on the left side is activated the robot 
            will first drive backwards and turn right*/
            case 0:
            for(int i=0; i<=Turns; i++){ 
                cmd_vel_pub.publish(DriveMsg(-0.2, 0.0));
                loop_rate.sleep();
            }
            for(int i=0; i<=Turns; i++){ 
                cmd_vel_pub.publish(DriveMsg(0.0, -(0.75)));
                loop_rate.sleep();
            }
            break;
            /*If a sensor on the middle is activated the robot 
            will drive backwards and turn left*/
            case 1:
            for(int i=0; i<=Turns; i++){ 
                cmd_vel_pub.publish(DriveMsg(-0.2, 0.0));
                loop_rate.sleep();
            }
            for(int i=0; i<=Turns; i++){
                cmd_vel_pub.publish(DriveMsg(0.0, (0.75)));
                loop_rate.sleep();
            }
            break;
            /*If a sensor on the right side is activated the robot 
            will drive backwards and turn left*/
            case 2:
            for(int i=0; i<=Turns; i++){ 
                cmd_vel_pub.publish(DriveMsg(-0.2, 0.0));
                loop_rate.sleep();
            }
            for(int i=0; i<=Turns; i++){
                cmd_vel_pub.publish(DriveMsg(0.0, (0.75)));
                loop_rate.sleep();
            }
            break;
        }
}

int main(int argc, char *argv[])
{
    /*The ROS node is initialized, and a nodehandle is declared*/
    ros::init(argc, argv, "Drive");
    ros::NodeHandle n;

    /*A ROS subscriber, and the publisher is assigned.*/
    ros::Subscriber miniproject_sub = n.subscribe("/miniproject/safety", 1, drive);
    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
    
    /*As long as ROS runs, check if the drive function has been called*/
    while (ros::ok)
    {
        if (PreCount != Count)
        {
            /*If the drive function has been called, call safetyAction with safety as parameter, 
            and note this has been done, by Precount = Count*/
            safetyAction(Sidehit);
            PreCount = Count;
        } else {
            /*If the drive function has not been called, drive straight*/
            cmd_vel_pub.publish(DriveMsg(0.0, 0.2));
        }
        /*Run the while loop once. This ensures that the node also checks the topics it subscribes to*/
        ros::spinOnce();
    }  
    /*Spin the node*/
    ros::spin();
    return 0;
}

/*The drive function is assigned*/
void drive(const b228_miniproject::safety_msg::ConstPtr& msg){
    /*Set the global variable safety as the side that was activated*/
    Sidehit = msg->side;
    /*Add one to count*/
    Count++;
}