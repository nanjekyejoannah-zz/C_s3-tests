#include "gtest/gtest.h"
#include <config4cpp/Configuration.h>
#include "libs3.h"
using namespace config4cpp;
using namespace std;

static void S3_init(void)
{
    Configuration *  cfg = Configuration::create();
    const char *     scope = "";
    const char *     configFile = "config.cfg";
    const char access_key[];
    const char secret_key[];
    const char host[];
    const char sample_bucket[];
    const char sample_key[];

    try {
        cfg->parse(configFile);
        access_key        = cfg->lookupString(scope, "access_key");
        secret_key        = cfg->lookupString(scope, "secret_key");
        host              = cfg->lookupString(scope, "host");
        sample_bucket     = cfg->lookupString(scope, "sample_bucket");
        sample_key        = cfg->lookupString(scope, "sample_key");
    } catch(const ConfigurationException & ex) {
        cerr << ex.c_str() << endl;
        cfg->destroy();
    }
    cout << "url=" << url << "; file=" << file
         << "; true_false=" << true_false
         << endl;
    cfg->destroy();

    

    S3_initialize("s3", S3_INIT_ALL, host);
}


TEST (BucketTest, delete_not_exist_bucket) { 

    s3_init();
    S3_delete_bucket(S3ProtocolHTTP, S3UriStylePath, access_key, 
        secret_key, host, sample_bucket, NULL, &responseHandler, NULL);
    EXPECT_NE (statusG, S3StatusOK);
    S3_deinitialize();
}

TEST (BucketTest, get__not_exist_bucket) { 
    s3_init();
    S3_get_bucket(S3ProtocolHTTP, S3UriStylePath, access_key, 
        secret_key, host, sample_bucket, NULL, &responseHandler, NULL);
    EXPECT_NE (statusG, S3StatusOK);
    S3_deinitialize();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}