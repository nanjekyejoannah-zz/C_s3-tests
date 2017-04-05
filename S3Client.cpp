/*
 *
 * creds, one of these choices,
 *  1, set ~/.aws/credentials
 *  2, point env AWS_SHARED_CREDENTIALS_FILE to credentials elsewhere
 *  3, set AWS_ACCESS_KEY_ID AWS_SECRET_ACCESS_KEY
 * and pass -e = radosgw (unless you want to test against amazon)
 */

#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/Bucket.h>
#include <aws/s3/model/CreateBucketRequest.h>
#include <aws/s3/model/ListObjectsRequest.h>
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

        const Aws::String bucket_name = "Bucket1";
        std::cout << "Creating S3 bucket: " << bucket_name << std::endl;

        Aws::S3::Model::CreateBucketRequest bucket_request;
        bucket_request.WithBucket(bucket_name);

        auto create_bucket_outcome = s3_client.CreateBucket(bucket_request);

        if (create_bucket_outcome.IsSuccess()) {
            std::cout << "Done!" << std::endl;
        } else {
            std::cout << "CreateBucket error: " <<
                create_bucket_outcome.GetError().GetExceptionName() << std::endl
                << create_bucket_outcome.GetError().GetMessage() << std::endl;
        }

        
        //List Buckets

  auto list_buckets_outcome = s3_client.ListBuckets();

  if (list_buckets_outcome.IsSuccess()) {
    std::cout << "Your Amazon S3 buckets:" << std::endl;

    Aws::Vector<Aws::S3::Model::Bucket> bucket_list =
      list_buckets_outcome.GetResult().GetBuckets();

    for (auto const &bucket: bucket_list) {
      std::cout << "* " << bucket.GetName() << std::endl;
    }
  } else {
    std::cout << "ListBuckets error: " <<
      list_buckets_outcome.GetError().GetExceptionName() << " " <<
      list_buckets_outcome.GetError().GetMessage() << std::endl;
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
    Aws::ShutdownAPI(options);
  }
  exit(exitcode);
}
