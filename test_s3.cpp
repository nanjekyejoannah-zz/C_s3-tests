/*
 * for creds set/export AWS_ACCESS_KEY_ID AWS_SECRET_ACCESS_KEY
 */
#include <aws/core/Aws.h>
#include <aws/s3/model/Bucket.h>
#include <aws/s3/model/CreateBucketRequest.h>
#include <aws/s3/model/DeleteBucketRequest.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/s3/model/Object.h>
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

//empty buckets should return no contents
TEST (BucketTest, bucket_list_empty) { 

  const Aws::String bucket_name = "Bucket2";
  Aws::S3::Model::CreateBucketRequest bucket_request;
  bucket_request.WithBucket(bucket_name);
  auto create_bucket_outcome = s3_client.CreateBucket(bucket_request);

  Aws::S3::Model::ListObjectsRequest objects_request;
  objects_request.WithBucket(bucket_name);
  auto list_objects_outcome = s3_client.ListObjects(objects_request);

  if (list_objects_outcome.IsSuccess()) 
  {
    Aws::Vector<Aws::S3::Model::Object> object_list = list_objects_outcome.GetResult().
    GetContents();
    EXPECT_EQ (0, object_list.size());
  }

}

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
