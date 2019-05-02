import argparse
import logging
import time
import csv

import cv2
import numpy as np
import serial

from tf_pose.estimator import TfPoseEstimator
from tf_pose.networks import get_graph_path, model_wh

logger = logging.getLogger('TfPoseEstimator-WebCam')
logger.setLevel(logging.DEBUG)
ch = logging.StreamHandler()
ch.setLevel(logging.DEBUG)
formatter = logging.Formatter('[%(asctime)s] [%(name)s] [%(levelname)s] %(message)s')
ch.setFormatter(formatter)
logger.addHandler(ch)

fps_time = 0


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='tf-pose-estimation realtime webcam')
    parser.add_argument('--camera', type=int, default=0)

    parser.add_argument('--resize', type=str, default='0x0',
                        help='if provided, resize images before they are processed. default=0x0, Recommends : 432x368 or 656x368 or 1312x736 ')
    parser.add_argument('--resize-out-ratio', type=float, default=4.0,
                        help='if provided, resize heatmaps before they are post-processed. default=1.0')

    parser.add_argument('--model', type=str, default='mobilenet_thin', help='cmu / mobilenet_thin / mobilenet_v2_large / mobilenet_v2_small')
    parser.add_argument('--show-process', type=bool, default=False,
                        help='for debug purpose, if enabled, speed for inference is dropped.')
    args = parser.parse_args()


    logger.debug('initialization %s : %s' % (args.model, get_graph_path(args.model)))
    w, h = model_wh(args.resize)
    if w > 0 and h > 0:
        e = TfPoseEstimator(get_graph_path(args.model), target_size=(w, h))
    else:
        e = TfPoseEstimator(get_graph_path(args.model), target_size=(432, 368))
    logger.debug('cam read+')
    cam = cv2.VideoCapture(args.camera)
    ret_val, image = cam.read()
    logger.info('cam image=%dx%d' % (image.shape[1], image.shape[0]))

    while True:
        ret_val, image = cam.read()

        logger.debug('ret_val')
        #logger.debug(image)

        logger.debug('image process+')
        humans = e.inference(image, resize_to_default=(w > 0 and h > 0), upsample_size=args.resize_out_ratio)



        '''
        Serial 
        '''
        serial_port = "/dev/cu.usbmodem14101"

        sendSerial = serial.Serial(serial_port, 9600)

        time.sleep(2)

        # int headX, int headY, int neckX, int neckY, int rShouX, int rShouY, int rElboX, int rElboY, int rHandX, int rHandY, int pelvX, int pelvY

        final_parts_dict = {}

        export_field_names = ['uidx', 'part_idx', 'x', 'y', 'score']
        for human in humans:
            body_parts = human.body_parts

            print("body_part")
            # print(body_parts.keys())
            print(body_parts.values())
            for body_part in body_parts.values():
                body_part_subdict = {"uidx": body_part.uidx, "part_idx": body_part.part_idx, "x": body_part.x,
                                     "y": body_part.y, "score": body_part.score}
                final_parts_dict[body_part.part_idx] = body_part_subdict

        logger.debug("final_parts_dict")
        logger.debug(final_parts_dict)

        # Nose = 0
        # Neck = 1
        # RShoulder = 2
        # RElbow = 3
        # RWrist = 4
        # LShoulder = 5
        # LElbow = 6
        # LWrist = 7
        # RHip = 8
        # RKnee = 9
        # RAnkle = 10
        # LHip = 11
        # LKnee = 12
        # LAnkle = 13
        # REye = 14
        # LEye = 15
        # REar = 16
        # LEar = 17
        # Background = 18
        x = "x"
        y = "y"

        parts_id_list = [0, 1, 2, 3, 4, 8]
        parts_list = []

        for id in parts_id_list:
            if id in final_parts_dict:
                parts_list.append(final_parts_dict[id][x])
                parts_list.append(final_parts_dict[id][y])
            else:
                parts_list.append(10)
                parts_list.append(10)

        # headX = final_parts_dict[0][x]
        # headY = final_parts_dict[0][y]
        # neckX = final_parts_dict[1][x]
        # neckY = final_parts_dict[1][y]
        # rShouX = final_parts_dict[2][x]
        # rShouY = final_parts_dict[2][y]
        # rElboX = final_parts_dict[3][x]
        # rElboY = final_parts_dict[3][y]
        # rHandX = final_parts_dict[4][x]
        # rHandY = final_parts_dict[4][y]
        # pelvX = final_parts_dict[8][x]
        # pelvY = final_parts_dict[8][y]
        #
        # parts_list = [headX, headY, neckX, neckY, ShouX, ShouY, rElboX, rElboY, rHandX, rHandY, pelvX, pelvY]


        sendSerial.write(str.encode('\n'.join(parts_list.join))

        '''
        End Serial
        '''


        #
        # '''
        # Implement output csv fuction
        # '''
        # csv_output_list = []
        # export_field_names = ['uidx', 'part_idx', 'x', 'y', 'score']
        # for human in humans:
        #     body_parts = human.body_parts
        #
        #     print("body_part")
        #     #print(body_parts.keys())
        #     print(body_parts.values())
        #     for body_part in body_parts.values():
        #         body_part_subdict = {"uidx": body_part.uidx, "part_idx": body_part.part_idx, "x": body_part.x, "y": body_part.y, "score": body_part.score}
        #        csv_output_list.append(body_part_subdict)

        #
        #
        # with open('body_parts_realtime_file.csv', mode='w') as body_parts_file:
        #     writer = csv.DictWriter(body_parts_file, fieldnames=export_field_names)
        #
        #     writer.writeheader()
        #     logger.info("update_extracted_features_csv: wrote header for extracted features CSV")
        #     for body_parts_list in csv_output_list:
        #         writer.writerow(body_parts_list)
        #
        #     #temp_file.flush()
        #     #repository.upload(temp_file.name, settings.PDF_EXTRACTED_FEATURES_CSV_S3_KEY, 'text/csv')
        #
        # '''
        # Finish implemennt output csv function
        # '''
        # # humans contains information stored like this
        # logger.debug("humans")
        # logger.debug(humans)
        #
        # logger.debug('postprocess+')
        # image = TfPoseEstimator.draw_humans(image, humans, imgcopy=False)
        #
        # logger.debug('show+')
        # cv2.putText(image,
        #             "FPS: %f" % (1.0 / (time.time() - fps_time)),
        #             (10, 10),  cv2.FONT_HERSHEY_SIMPLEX, 0.5,
        #             (0, 255, 0), 2)
        # cv2.imshow('tf-pose-estimation result', image)
        # fps_time = time.time()
        # if cv2.waitKey(1) == 27:
        #     break
        # logger.debug('finished+')

    cv2.destroyAllWindows()
