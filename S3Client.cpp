/*
 * for creds set/export AWS_ACCESS_KEY_ID AWS_SECRET_ACCESS_KEY
 * and pass -e = localhost:8000 if using vstart.sh 
 */

#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/Bucket.h>
#include <aws/s3/model/CreateBucketRequest.h>
#include <aws/s3/model/DeleteBucketRequest.h>
#include <network/uri.hpp>


const char *my_endpoint;
const char *my_region;

int exitcode;

int process()
{
  Aws::Client::ClientConfiguration clientconfig;
  if (my_region)
    clientconfig.region = my_region;
  if (my_endpoint) {
    Aws::String aws_my_endpoint(my_endpoint);
    network::uri u(my_endpoint);
    auto us = u.scheme().to_string();
    if (!us.compare("http")) {
      clientconfig.scheme = Aws::Http::Scheme::HTTP;
    }
    else if (!us.compare("https")) {
      clientconfig.scheme = Aws::Http::Scheme::HTTPS;
    } else {
      throw std::out_of_range("invalid scheme " + us);
    }
    std::string ur;
    ur = u.host().to_string();
    if (u.has_port()) {
      ur += ":" + u.port().to_string();
    }
    clientconfig.endpointOverride = ur.c_str();
  }

  Aws::S3::S3Client s3_client(clientconfig);

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

  TEST (BucketTest, delete_non_existant_bucket) { 
    const Aws::String bucket_name = "SomeBucket";
    Aws::S3::Model::DeleteBucketRequest bucket_request;
    bucket_request.WithBucket(bucket_name);
    auto delete_bucket_outcome = s3_client.DeleteBucket(bucket_request);
    EXPECT_EQ (false, delete_bucket_outcome.IsSuccess()); 
  }
  
}

int main(int ac, char **av)
{
  char *ap;
  while (--ac > 0) if (*(ap = *++av) == '-') while (*++ap) switch(*ap) {
  case 'e':
    if (--ac <= 0) {
      std::cerr << "-e: missing endpoint " << std::endl;
      goto Usage;
    }
    my_endpoint = *++av;
    my_region = "mexico";
    break;
  case '-':
    break;
  default:
    std::cerr << "bad flag " << *ap << std::endl;
  Usage:
    std::cerr << "Usage: lb2 [-e endpoint]" << std::endl;
    exit(1);
  }
  {
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    process();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    Aws::ShutdownAPI(options);
  }
  exit(exitcode);
}
