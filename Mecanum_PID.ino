#include <Arduino.h>

// PID制御のゲイン
float kp[4] = {1.0, 1.0, 1.0, 1.0};
float ki[4] = {0.5, 0.5, 0.5, 0.5};
float kd[4] = {0.1, 0.1, 0.1, 0.1};

// 移動距離の目標設定（mm単位）
float targetDistance[4]; // 各ホイールの移動距離目標

// エンコーダ関連の設定
const float wheelDiameter = 80.0; // ホイールの直径（mm）
const float encoderPulsesPerRevolution = 750; // エンコーダの1回転あたりのパルス数
const float distancePerCount = (PI * wheelDiameter) / encoderPulsesPerRevolution; // 1カウントあたりの距離（mm）

// PID制御に関する変数
float integral[4] = {0, 0, 0, 0};
float previous_error[4] = {0, 0, 0, 0};

// PID制御計算
float pidCompute(int index, float target, float current)
{
  float error = target - current;
  integral[index] += error;
  float derivative = error - previous_error[index];
  float output = kp[index] * error + ki[index] * integral[index] + kd[index] * derivative;
  previous_error[index] = error;
  return constrain(output, -255, 255); // PWMの範囲に制約
}

void setup()
{
  
}

void loop()
{
  for (int i = 0; i < 4; i++)
  {
    float currentDistance = encoderCount[i] * distancePerCount; // 現在の移動距離
    float controlSignal = pidCompute(i, targetDistance[i], currentDistance);

    // 制御信号に基づいてモーターを駆動
    driveMotor(i, controlSignal);
  }
  
}
