//
// Created by ss on 19-1-14.
//
#include <thundergbm/parser.h>
#include <thundergbm/trainer.h>
#include "gtest/gtest.h"
#include "thundergbm/common.h"

class TrainTest : public ::testing::Test {
public:
    GBMParam param;
    TreeTrainer trainer;
protected:
    void SetUp() override {
        param.depth = 6;
        param.n_trees = 40;
        param.n_device = 1;
        param.min_child_weight = 1;
        param.lambda = 1;
        param.gamma = 1;
        param.rt_eps = 1e-6;
        param.max_num_bin = 255;
        param.verbose = false;
        param.profiling = false;
        param.column_sampling_rate = 1;
        param.bagging = false;
        param.n_parallel_trees = 1;
        param.learning_rate = 1;
        param.objective = "reg:linear";
        param.num_class = 1;
        param.path = "../dataset/test_dataset.txt";
        param.out_model_name = "tgbm.model";
        param.in_model_name = "tgbm.model";
        param.tree_method = "auto";
        if (!param.verbose) {
            el::Loggers::reconfigureAllLoggers(el::Level::Debug, el::ConfigurationType::Enabled, "false");
            el::Loggers::reconfigureAllLoggers(el::Level::Trace, el::ConfigurationType::Enabled, "false");
        }
        if (!param.profiling) {
            el::Loggers::reconfigureAllLoggers(el::ConfigurationType::PerformanceTracking, "false");
        }
    }

    void TearDown() override {
    }
};

TEST_F(TrainTest, news20) {
    param.path = DATASET_DIR "news20.scale";
    float_type rmse = trainer.train(param);
    EXPECT_NEAR(rmse, 2.55274, 1e-5);
}

TEST_F(TrainTest, covtype) {
    param.path = DATASET_DIR "covtype";
    float_type rmse = trainer.train(param);
    EXPECT_NEAR(rmse, 0.730795, 1e-5);
}

TEST_F(TrainTest, covtype_multiclass) {
    param.path = DATASET_DIR "covtype";
    param.num_class = 7;
    param.objective = "multi:softprob";
    float_type rmse = trainer.train(param);
}
