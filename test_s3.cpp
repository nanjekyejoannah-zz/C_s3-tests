/*
 * for creds set/export AWS_ACCESS_KEY_ID AWS_SECRET_ACCESS_KEY
 * and pass -e = localhost:8000 if using vstart.sh 
 */

#include <aws/core/Aws.h>
#include <aws/s3/model/Bucket.h>
#include <aws/s3/model/CreateBucketRequest.h>
#include <aws/s3/model/DeleteBucketRequest.h>
#include <network/uri.hpp>


TEST (BucketTest, delete_non_existant_bucket) { 
  const Aws::String bucket_name = "SomeBucket";
  Aws::S3::Model::DeleteBucketRequest bucket_request;
  bucket_request.WithBucket(bucket_name);
  auto delete_bucket_outcome = s3_client.DeleteBucket(bucket_request);
  EXPECT_EQ (false, delete_bucket_outcome.IsSuccess()); 
}

TEST (BucketTest, list_buckets) { 
  auto list_buckets_outcome = s3_client.ListBuckets();
  EXPECT_EQ (true, list_buckets_outcome.IsSuccess());
}

// // empty buckets return no contents
// TEST (BucketTest, bucket_list_empty) { 

//   const Aws::String bucket_name = "Bucket2";
//   Aws::S3::Model::CreateBucketRequest bucket_request;
//   bucket_request.WithBucket(bucket_name);
//   auto create_bucket_outcome = s3_client.CreateBucket(bucket_request);
// }

int main(int argc, char **argv)
{
  
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }
    Aws::ShutdownAPI(options);

    return 0;

}
