#include <iostream>

#include <opencv2/opencv.hpp> 

cv::Mat map_process(cv::Mat &map_source_img,
    int loop_time, double map_resolution,
    double room_area_factor_lower_limit,
    double room_area_factor_upper_limit);

cv::Mat image_segmentation_method(cv::Mat &Original_Map_from_subscription, 
        int loop_time,
		double map_resolution_data_from_subscription, 
		// double map_sampling_factor_, 
		double room_area_factor_lower_limit_, 
		double room_area_factor_upper_limit_);

int main(int argc, char **argv) {
    cv::Mat map_img = cv::imread("./map.png", CV_LOAD_IMAGE_GRAYSCALE);
	//cv::Mat map_img = cv::imread("/home/ismart/tmp/map.png");
	//cv::cvtColor(map_img, map_img, CV_BGR2GRAY);
    int loop_time = 8;
    if(argc > 0){
        loop_time = int(*argv[1]);
    }
    cv::Mat result = map_process(map_img, loop_time, 0.05, 3.0, 40.0);
    cv::Mat result2 = image_segmentation_method(map_img, loop_time, 0.05, 3.0, 40.0);
    //cv::imshow("1", result);
    //cv::waitKey();
	cv::imwrite("segmented_map.png", result);
	cv::imwrite("segmented_map2.png", result2);
	return 0;
}

cv::Mat map_process(cv::Mat &map_source_img,
    int loop_time, double map_resolution, 
    double room_area_factor_lower_limit,
    double room_area_factor_upper_limit) {
    // cv::Mat temporary_map_to_get_the_contours_of_the_room  = map_source_img.clone();
    cv::Mat map_img_buf = map_source_img.clone();
    std::vector<std::vector<cv::Point> > temporary_contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<std::vector<cv::Point> > saved_contours_;

    for (int loop_idx = 0; loop_idx < loop_time; loop_idx++) {
        cv::erode(map_img_buf, map_img_buf, cv::Mat(), cv::Point(-1, -1), 1);
        // cv::imshow("1", map_img_buf);
        // cv::waitKey(0);
        // cv::imwrite("map_img_buf.png", map_img_buf);

        cv::Mat contour_map = map_img_buf.clone();
        // cv::imwrite("contour_map_before_find.png", contour_map);
        cv::findContours(contour_map, temporary_contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_TC89_L1);
        // std::cout<<"temporary_contours size: " << temporary_contours.size() << std::endl;
        // cv::imwrite("contour_map_before_draw.png", contour_map);
        cv::drawContours(contour_map, temporary_contours, -1, cv::Scalar(128, 128, 128, 128), 2);
        // cv::imwrite("contour_map_after_draw.png", contour_map);

        for (int idx = 0; idx >= 0; idx = hierarchy[idx][0])
        {
            double room_area = map_resolution * map_resolution * cv::contourArea(temporary_contours[idx]);
            
            //4. for each contour check if contour fulfills criteria of a room
            if (room_area_factor_lower_limit < room_area && room_area < room_area_factor_upper_limit && temporary_contours.size() != 0)
            {
                //5. if contour fulfill the criteria save the contour somewhere else
                saved_contours_.push_back(temporary_contours[idx]);

                //************Remove the Saved Contour or make the region Black************#画轮廓点
                cv::drawContours(map_img_buf, temporary_contours, idx, cv::Scalar(0), CV_FILLED, 8, hierarchy, 2);
                //************Remove the Saved Contour or make the region Black************
            }
        }
    }
    // cv::imwrite("map_with_contours.png", map_img_buf);
    std::cout<<"Output room numbers." << "\nSegmentation found " << saved_contours_.size() << " rooms."  << std::endl;
    cv::Mat new_map_to_draw_the_saved_contours_of_the_room = map_source_img.clone();
    for (unsigned int idx = 0; idx < saved_contours_.size(); idx++)
    {
        std::cout << "Segmentation found " << saved_contours_.size() << " rooms." << std::endl;
        //0-for obstacles and it's a black pixel
        //255-for white value and accessible area
        cv::Scalar color_to_fill(rand() % 253 + 1);
        cv::drawContours(new_map_to_draw_the_saved_contours_of_the_room, saved_contours_, idx, color_to_fill, -1);
    }
    // exit(0);
    
    cv::Mat new_map_with_obstacles_info = new_map_to_draw_the_saved_contours_of_the_room.clone();
    std::vector<cv::Point> black_pixel;

    for (int y_coordinate = 0; y_coordinate < map_source_img.cols; y_coordinate++)
    {
        for (int x_coordinate = 0; x_coordinate < map_source_img.rows; x_coordinate++)
        {
            if (map_source_img.at<unsigned char>(x_coordinate, y_coordinate) == 0)
            {
                black_pixel.push_back(cv::Point(y_coordinate, x_coordinate));
            }
        }
    }
    // cv::imshow("2", new_map_with_obstacles_info);
    // cv::waitKey(0);
    std::cout << new_map_with_obstacles_info.cols << '\t' << new_map_with_obstacles_info.rows << std::endl;
    for (unsigned int idx = 0; idx < black_pixel.size(); idx++)
    {
        //std::cout << black_pixel[idx] << std::endl;
        new_map_with_obstacles_info.at<unsigned char>(black_pixel[idx].y, black_pixel[idx].x) = 0;
    }

    cv::Mat complete_map_after_contour_extraction_and_labelling = new_map_with_obstacles_info.clone();
    int map_column_length, map_row_length = 0;

    cv::Mat temporary_map_for_replica_padding_purpose = new_map_with_obstacles_info.clone();
    std::vector<cv::Point> neighbourhood_pixel;

    for (int loop_counter = 0; loop_counter < 1000; loop_counter++)
    {
        //std::cout << loop_counter << std::endl;
        for (map_column_length = 0; map_column_length < map_source_img.cols; map_column_length++)
        {
            for (map_row_length = 0; map_row_length < map_source_img.rows; map_row_length++)
            {
                if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length) != 0
                    && complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length) != 255)
                {
                    //Check every Pixel where its neighborhood is already replaced or not
                    if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length - 1, map_column_length - 1) == 255
                        && temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length - 1, map_column_length - 1)
                        != complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
                    {
                        neighbourhood_pixel.push_back(cv::Point(map_column_length - 1, map_row_length - 1));
                    }

                    if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length - 1, map_column_length) == 255
                        && temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length - 1, map_column_length)
                        != complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
                    {
                        neighbourhood_pixel.push_back(cv::Point(map_column_length, map_row_length - 1));
                    }

                    if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length - 1, map_column_length + 1) == 255
                        && temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length - 1, map_column_length + 1)
                        != complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
                    {
                        neighbourhood_pixel.push_back(cv::Point(map_column_length + 1, map_row_length - 1));
                    }

                    if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length - 1) == 255
                        && temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length - 1)
                        != complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
                    {
                        neighbourhood_pixel.push_back(cv::Point(map_column_length - 1, map_row_length));
                    }

                    if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length + 1) == 255
                        && temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length + 1)
                        != complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
                    {
                        neighbourhood_pixel.push_back(cv::Point(map_column_length + 1, map_row_length));
                    }

                    if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length + 1, map_column_length - 1) == 255
                        && temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length + 1, map_column_length - 1)
                        != complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
                    {
                        neighbourhood_pixel.push_back(cv::Point(map_column_length - 1, map_row_length + 1));
                    }

                    if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length + 1, map_column_length) == 255
                        && temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length + 1, map_column_length)
                        != complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
                    {
                        neighbourhood_pixel.push_back(cv::Point(map_column_length, map_row_length + 1));
                    }

                    if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length + 1, map_column_length + 1) == 255
                        && temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length + 1, map_column_length + 1)
                        != complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
                    {
                        neighbourhood_pixel.push_back(cv::Point(map_column_length + 1, map_row_length + 1));
                    }
                }

                for (unsigned int idx = 0; idx < neighbourhood_pixel.size(); idx++)
                {
                    if (neighbourhood_pixel.size() != 0)
                        temporary_map_for_replica_padding_purpose.at<unsigned char>(neighbourhood_pixel[idx]) = complete_map_after_contour_extraction_and_labelling.at<
                        unsigned char>(map_row_length, map_column_length);
                }
                neighbourhood_pixel.clear();
            }

        }
        //Go for Next Check where the Replaced Pixel are now set as original
        complete_map_after_contour_extraction_and_labelling = temporary_map_for_replica_padding_purpose.clone();
    }

    cv::Mat bounding_box_map_to_extract_room_info = temporary_map_for_replica_padding_purpose.clone();
    cv::Point point_at_the_min_end_of_xy_coordinate, point_at_the_max_end_of_xy_coordinate, center_of_the_individual_room;

    std::vector<int> min_y_value_of_the_room(255, 100000000);
    std::vector<int> max_y_value_of_the_room(255, 0);
    std::vector<int> min_x_value_of_the_room(255, 100000000);
    std::vector<int> max_x_value_of_the_room(255, 0);

    for (map_column_length = 0; map_column_length < map_source_img.cols; map_column_length++)
    {
        for (map_row_length = 0; map_row_length < map_source_img.rows; map_row_length++)
        {
            if (bounding_box_map_to_extract_room_info.at<unsigned char>(map_row_length, map_column_length) != 0
                && bounding_box_map_to_extract_room_info.at<unsigned char>(map_row_length, map_column_length) != 255)
            {
                min_y_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)] = std::min(map_column_length,
                    min_y_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)]);
                max_y_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)] = std::max(map_column_length,
                    max_y_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)]);
                min_x_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)] = std::min(map_row_length,
                    min_x_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)]);
                max_x_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)] = std::max(map_row_length,
                    max_x_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)]);

            }
        }
    }

    //房间四个交点坐标及中心坐标
    std::vector<int> minimum_x_coordinate_value_of_the_room;
    std::vector<int> minimum_y_coordinate_value_of_the_room;
    std::vector<int> maximum_x_coordinate_value_of_the_room;
    std::vector<int> maximum_y_coordinate_value_of_the_room;
    std::vector<int> x_coordinate_value_of_the_room_center_;
    std::vector<int> y_coordinate_value_of_the_room_center_;

    std::vector<cv::Point> center_of_roo;

    for (unsigned int loop_counter = 0; loop_counter < min_y_value_of_the_room.size(); loop_counter++)
    {
        if (min_y_value_of_the_room[loop_counter] != 100000000 && min_x_value_of_the_room[loop_counter] != 100000000 && max_y_value_of_the_room[loop_counter] != 0
            && max_x_value_of_the_room[loop_counter] != 0)
        {
            point_at_the_min_end_of_xy_coordinate.x = min_y_value_of_the_room[loop_counter];
            point_at_the_min_end_of_xy_coordinate.y = min_x_value_of_the_room[loop_counter];
            point_at_the_max_end_of_xy_coordinate.x = max_y_value_of_the_room[loop_counter];
            point_at_the_max_end_of_xy_coordinate.y = max_x_value_of_the_room[loop_counter];

            center_of_the_individual_room.x = min_y_value_of_the_room[loop_counter] + (max_y_value_of_the_room[loop_counter] - min_y_value_of_the_room[loop_counter]) / 2;
            center_of_the_individual_room.y = min_x_value_of_the_room[loop_counter] + (max_x_value_of_the_room[loop_counter] - min_x_value_of_the_room[loop_counter]) / 2;

#ifdef __DEBUG_DISPLAYS__
            ROS_INFO("Center of the bounding Box: [ %d , %d ]", center_of_the_individual_room.x, center_of_the_individual_room.y);
#endif

            minimum_x_coordinate_value_of_the_room.push_back(min_x_value_of_the_room[loop_counter]);
            minimum_y_coordinate_value_of_the_room.push_back(min_y_value_of_the_room[loop_counter]);
            maximum_x_coordinate_value_of_the_room.push_back(max_x_value_of_the_room[loop_counter]);
            maximum_y_coordinate_value_of_the_room.push_back(max_y_value_of_the_room[loop_counter]);

            center_of_roo.push_back(center_of_the_individual_room);
            x_coordinate_value_of_the_room_center_.push_back(center_of_the_individual_room.x);
            y_coordinate_value_of_the_room_center_.push_back(center_of_the_individual_room.y);

            cv::rectangle(bounding_box_map_to_extract_room_info, point_at_the_min_end_of_xy_coordinate, point_at_the_max_end_of_xy_coordinate, cv::Scalar(255), 1);
            cv::circle(bounding_box_map_to_extract_room_info, center_of_the_individual_room, 3, cv::Scalar(255), -1);
        }
    }

#ifdef __DEBUG_DISPLAYS__
    cv::Mat Debug_image = temporary_map_for_replica_padding_purpose.clone();
    cv::imshow("segmented map", Debug_image);
    cv::waitKey(100);
    cv::imshow("bounding box", bounding_box_map_to_extract_room_info);
    cv::waitKey(100);
#endif

    //************Extracting Data from segmented map and Bounding Box Technique**********************************
    
    /*
    for (int i = 0; i < minimum_x_coordinate_value_of_the_room.size(); i++){
        cv::Mat img = cv::imread("./map.png");
        cv::circle(img, cv::Point(minimum_y_coordinate_value_of_the_room[i], minimum_x_coordinate_value_of_the_room[i]), 2, (0, 255, 0), 2);
        cv::circle(img, cv::Point(maximum_y_coordinate_value_of_the_room[i], minimum_x_coordinate_value_of_the_room[i]), 2, (0, 255, 0), 2);
        cv::circle(img, cv::Point(minimum_y_coordinate_value_of_the_room[i], maximum_x_coordinate_value_of_the_room[i]), 2, (0, 255, 0), 2);
        cv::circle(img, cv::Point(maximum_y_coordinate_value_of_the_room[i], maximum_x_coordinate_value_of_the_room[i]), 2, (0, 255, 0), 2);
        cv::circle(img, cv::Point(y_coordinate_value_of_the_room_center_[i], x_coordinate_value_of_the_room_center_[i]), 2, (0, 0, 255), 2);
        cv::imshow("segmented map", img);
        cv::waitKey();
    }
    */
    return temporary_map_for_replica_padding_purpose.clone();
}

cv::Mat image_segmentation_method(cv::Mat &Original_Map_from_subscription, 
        int loop_time,
		double map_resolution_data_from_subscription, 
		// double map_sampling_factor_, 
		double room_area_factor_lower_limit_, 
		double room_area_factor_upper_limit_)
{
	double map_resolution_ = map_resolution_data_from_subscription;
	double room_area_;
	
	std::cout<< __FUNCTION__ <<"\n";
	//1. collect the navigation data from analyze map action client
	//cv::imread("/home/ismart/Pictures/map.png");
	cv::Mat temporary_map_to_get_the_contours_of_the_room_ = Original_Map_from_subscription.clone();
	cv::Mat new_map_to_draw_the_saved_contours_of_the_room_ = Original_Map_from_subscription.clone();
	cv::Mat expanded_map_;
	cv::Mat contour_map_;
	cv::Mat new_map_with_obstacles_info_;
	cv::Mat complete_map_after_contour_extraction_and_labelling;
	cv::Mat temporary_map_for_replica_padding_purpose;
	// cv::Mat bounding_box_map_to_extract_room_info;
	std::vector<std::vector<cv::Point> > temporary_contours_;
	std::vector<cv::Vec4i> hierarchy_;
	std::vector<cv::Point> black_pixel_;
	std::vector<cv::Point> neighbourhood_pixel_;
	std::vector<int> minimum_x_coordinate_value_of_the_room_;
	std::vector<int> maximum_x_coordinate_value_of_the_room_;
	std::vector<int> minimum_y_coordinate_value_of_the_room_;
	std::vector<int> maximum_y_coordinate_value_of_the_room_;
	std::vector<cv::Point> center_of_room_;
	std::vector<std::vector<cv::Point> > saved_contours_;
	std::vector<int> x_coordinate_value_of_the_room_center_;
	std::vector<int> y_coordinate_value_of_the_room_center_;
	// cv::Mat temporary_map_to_get_the_contours_of_the_room_ = cv::imread("/home/ismart/Pictures/map.png");
	// cv::Mat new_map_to_draw_the_saved_contours_of_the_room_ = cv::imread("/home/ismart/Pictures/map.png");
	// Original_Map_from_subscription.copyTo(temporary_map_to_get_the_contours_of_the_room_);
	// Original_Map_from_subscription.copyTo(new_map_to_draw_the_saved_contours_of_the_room_);
	
	//2. erode the image until get the last room
	// for (int for_loop_counter = 0; for_loop_counter < map_sampling_factor_ / map_resolution_; for_loop_counter++)
	for (int for_loop_counter = 0; for_loop_counter < loop_time; for_loop_counter++)
	{
		cv::erode(temporary_map_to_get_the_contours_of_the_room_, expanded_map_, cv::Mat(), cv::Point(-1, -1), 1);
		temporary_map_to_get_the_contours_of_the_room_ = expanded_map_;
		contour_map_ = expanded_map_.clone();
		// ROS_INFO("Program exit.");
		// exit(0);
		//*********************** Find contours and Draw Contours*******************

		//3. find contours
		cv::findContours(contour_map_, temporary_contours_, hierarchy_, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		cv::drawContours(contour_map_, temporary_contours_, -1, cv::Scalar(128, 128, 128, 128), 2);

		for (int idx = 0; idx >= 0; idx = hierarchy_[idx][0])
		{
			room_area_ = map_resolution_ * map_resolution_ * cv::contourArea(temporary_contours_[idx]);

			//4. for each contour check if contour fulfills criteria of a room
			if (room_area_factor_lower_limit_ < room_area_ && room_area_ < room_area_factor_upper_limit_ && temporary_contours_.size() != 0)
			{
				//5. if contour fulfill the criteria save the contour somewhere else
				saved_contours_.push_back(temporary_contours_[idx]);

				//************Remove the Saved Contour or make the region Black************
				cv::drawContours(temporary_map_to_get_the_contours_of_the_room_, temporary_contours_, idx, cv::Scalar(0), CV_FILLED, 8, hierarchy_, 2);
				//************Remove the Saved Contour or make the region Black************
			}
		}
	} //6. exit the loop if there are no more contours
	

	//**********************Draw the saved Contours in the clone version of original image***************

	for (unsigned int idx = 0; idx < saved_contours_.size(); idx++)
	{
		std::cout << "Segmentation found " << saved_contours_.size() << " rooms." << std::endl;
		//0-for obstacles and it's a black pixel
		//255-for white value and accessible area
		cv::Scalar color_to_fill(rand() % 253 + 1);
		cv::drawContours(new_map_to_draw_the_saved_contours_of_the_room_, saved_contours_, idx, color_to_fill, -1);
	}

	//**********************Draw the saved Contours in the clone version of original image***************

	//*********** To draw the Obstacle in the modified map*********************

	new_map_with_obstacles_info_ = new_map_to_draw_the_saved_contours_of_the_room_.clone();

	for (int y_coordinate = 0; y_coordinate < Original_Map_from_subscription.cols; y_coordinate++)
	{
		for (int x_coordinate = 0; x_coordinate < Original_Map_from_subscription.rows; x_coordinate++)
		{
			if (Original_Map_from_subscription.at<unsigned char>(x_coordinate, y_coordinate) == 0)
			{
				black_pixel_.push_back(cv::Point(y_coordinate, x_coordinate));
			}
		}
	}

	for (unsigned int idx = 0; idx < black_pixel_.size(); idx++)
	{
		new_map_with_obstacles_info_.at<unsigned char>(black_pixel_[idx]) = 0;
	}

	//*********** To draw the Obstacle in the modified map*********************

	//************Replica-Padding to the Image region*************

	//7. copy original image
	complete_map_after_contour_extraction_and_labelling = new_map_with_obstacles_info_.clone();
	int map_column_length, map_row_length = 0;

	temporary_map_for_replica_padding_purpose = new_map_with_obstacles_info_.clone();

	// 8. copy the stored contours into the map and fill each with a unique
	//    id number repeat until convergence(i.e there are no more white pixels)
	for (int loop_counter = 0; loop_counter < 1000; loop_counter++)
	{
		for (map_column_length = 0; map_column_length < Original_Map_from_subscription.cols; map_column_length++)
		{
			for (map_row_length = 0; map_row_length < Original_Map_from_subscription.rows; map_row_length++)
			{
				if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length) != 0
						&& complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length) != 255)
				{
					//Check every Pixel where its neighborhood is already replaced or not
					if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length - 1, map_column_length - 1) == 255
							&& temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length - 1, map_column_length - 1)
									!= complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
					{
						neighbourhood_pixel_.push_back(cv::Point(map_column_length - 1, map_row_length - 1));
					}

					if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length - 1, map_column_length) == 255
							&& temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length - 1, map_column_length)
									!= complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
					{
						neighbourhood_pixel_.push_back(cv::Point(map_column_length, map_row_length - 1));
					}

					if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length - 1, map_column_length + 1) == 255
							&& temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length - 1, map_column_length + 1)
									!= complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
					{
						neighbourhood_pixel_.push_back(cv::Point(map_column_length + 1, map_row_length - 1));
					}

					if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length - 1) == 255
							&& temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length - 1)
									!= complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
					{
						neighbourhood_pixel_.push_back(cv::Point(map_column_length - 1, map_row_length));
					}

					if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length + 1) == 255
							&& temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length + 1)
									!= complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
					{
						neighbourhood_pixel_.push_back(cv::Point(map_column_length + 1, map_row_length));
					}

					if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length + 1, map_column_length - 1) == 255
							&& temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length + 1, map_column_length - 1)
									!= complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
					{
						neighbourhood_pixel_.push_back(cv::Point(map_column_length - 1, map_row_length + 1));
					}

					if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length + 1, map_column_length) == 255
							&& temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length + 1, map_column_length)
									!= complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
					{
						neighbourhood_pixel_.push_back(cv::Point(map_column_length, map_row_length + 1));
					}

					if (complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length + 1, map_column_length + 1) == 255
							&& temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length + 1, map_column_length + 1)
									!= complete_map_after_contour_extraction_and_labelling.at<unsigned char>(map_row_length, map_column_length))
					{
						neighbourhood_pixel_.push_back(cv::Point(map_column_length + 1, map_row_length + 1));
					}
				}

				for (unsigned int idx = 0; idx < neighbourhood_pixel_.size(); idx++)
				{
					if (neighbourhood_pixel_.size() != 0)
						temporary_map_for_replica_padding_purpose.at<unsigned char>(neighbourhood_pixel_[idx]) = complete_map_after_contour_extraction_and_labelling.at<
								unsigned char>(map_row_length, map_column_length);
				}
				neighbourhood_pixel_.clear();
			}

		}
		//Go for Next Check where the Replaced Pixel are now set as original
		complete_map_after_contour_extraction_and_labelling = temporary_map_for_replica_padding_purpose.clone();
	}

	//************Replica-Padding to the Image region*************

	//************Extracting Data from segmented map and Bounding Box Technique**********************************

	cv::Mat bounding_box_map_to_extract_room_info = temporary_map_for_replica_padding_purpose.clone();
	cv::Point point_at_the_min_end_of_xy_coordinate, point_at_the_max_end_of_xy_coordinate, center_of_the_individual_room;

	std::vector<int> min_y_value_of_the_room(255, 100000000);
	std::vector<int> max_y_value_of_the_room(255, 0);
	std::vector<int> min_x_value_of_the_room(255, 100000000);
	std::vector<int> max_x_value_of_the_room(255, 0);

	for (map_column_length = 0; map_column_length < Original_Map_from_subscription.cols; map_column_length++)
	{
		for (map_row_length = 0; map_row_length < Original_Map_from_subscription.rows; map_row_length++)
		{
			if (bounding_box_map_to_extract_room_info.at<unsigned char>(map_row_length, map_column_length) != 0
					&& bounding_box_map_to_extract_room_info.at<unsigned char>(map_row_length, map_column_length) != 255)
			{
				min_y_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)] = std::min(map_column_length,
						min_y_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)]);
				max_y_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)] = std::max(map_column_length,
						max_y_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)]);
				min_x_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)] = std::min(map_row_length,
						min_x_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)]);
				max_x_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)] = std::max(map_row_length,
						max_x_value_of_the_room[temporary_map_for_replica_padding_purpose.at<unsigned char>(map_row_length, map_column_length)]);

			}
		}
	}

	for (unsigned int loop_counter = 0; loop_counter < min_y_value_of_the_room.size(); loop_counter++)
	{
		if (min_y_value_of_the_room[loop_counter] != 100000000 && min_x_value_of_the_room[loop_counter] != 100000000 && max_y_value_of_the_room[loop_counter] != 0
				&& max_x_value_of_the_room[loop_counter] != 0)
		{
			point_at_the_min_end_of_xy_coordinate.x = min_y_value_of_the_room[loop_counter];
			point_at_the_min_end_of_xy_coordinate.y = min_x_value_of_the_room[loop_counter];
			point_at_the_max_end_of_xy_coordinate.x = max_y_value_of_the_room[loop_counter];
			point_at_the_max_end_of_xy_coordinate.y = max_x_value_of_the_room[loop_counter];

			center_of_the_individual_room.x = min_y_value_of_the_room[loop_counter] + (max_y_value_of_the_room[loop_counter] - min_y_value_of_the_room[loop_counter]) / 2;
			center_of_the_individual_room.y = min_x_value_of_the_room[loop_counter] + (max_x_value_of_the_room[loop_counter] - min_x_value_of_the_room[loop_counter]) / 2;

#ifdef __DEBUG_DISPLAYS__
	ROS_INFO("Center of the bounding Box: [ %d , %d ]", center_of_the_individual_room.x  , center_of_the_individual_room.y);
#endif

			minimum_x_coordinate_value_of_the_room_.push_back(min_x_value_of_the_room[loop_counter]);
			minimum_y_coordinate_value_of_the_room_.push_back(min_y_value_of_the_room[loop_counter]);
			maximum_x_coordinate_value_of_the_room_.push_back(max_x_value_of_the_room[loop_counter]);
			maximum_y_coordinate_value_of_the_room_.push_back(max_y_value_of_the_room[loop_counter]);

			center_of_room_.push_back(center_of_the_individual_room);
			x_coordinate_value_of_the_room_center_.push_back(center_of_the_individual_room.x);
			y_coordinate_value_of_the_room_center_.push_back(center_of_the_individual_room.y);

			cv::rectangle(bounding_box_map_to_extract_room_info, point_at_the_min_end_of_xy_coordinate, point_at_the_max_end_of_xy_coordinate, cv::Scalar(255), 1);
			cv::circle(bounding_box_map_to_extract_room_info, center_of_the_individual_room, 3, cv::Scalar(255), -1);
		}
	}
#ifdef __DEBUG_DISPLAYS__
	cv::Mat Debug_image = temporary_map_for_replica_padding_purpose.clone();
	cv::imshow( "segmented map", Debug_image );
	cv::waitKey(100);
	cv::imshow("bounding box", bounding_box_map_to_extract_room_info);
	cv::waitKey(100);
#endif

	//************Extracting Data from segmented map and Bounding Box Technique**********************************
	return temporary_map_for_replica_padding_purpose;
}