#include "S3buckets.h"
#include "pch.h"
// S3 - Files upload/download/...
#include <aws/s3/S3Client.h>
#include <aws/s3/model/CreateBucketRequest.h>
// List buckets
#include <aws/s3/model/Bucket.h>
// Delete buckets
#include <aws/s3/model/DeleteBucketRequest.h>


void ListBucket() {

    Aws::S3::S3Client s3_client;
    auto outcome = s3_client.ListBuckets();

    if (outcome.IsSuccess())
    {
        std::cout << "Your Amazon S3 buckets:" << std::endl;

        Aws::Vector<Aws::S3::Model::Bucket> bucket_list =
            outcome.GetResult().GetBuckets();

        for (auto const& bucket : bucket_list)
        {
            std::cout << "  * " << bucket.GetName() << std::endl;
        }
    }
    else
    {
        std::cout << "ListBuckets error: "
            << outcome.GetError().GetExceptionName() << " - "
            << outcome.GetError().GetMessage() << std::endl;
    }
}

void DeleteBucket()
{


    Aws::String user_region = "EU";
    Aws::String bucket_name = "bucketName";

    Aws::Client::ClientConfiguration config;
    config.region = user_region;
    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::DeleteBucketRequest bucket_request;
    bucket_request.SetBucket(bucket_name);

    auto outcome = s3_client.DeleteBucket(bucket_request);

    if (outcome.IsSuccess())
    {
        std::cout << "Done!" << std::endl;
    }
    else
    {
        std::cout << "DeleteBucket error: "
            << outcome.GetError().GetExceptionName() << " - "
            << outcome.GetError().GetMessage() << std::endl;
    }
}


bool create_bucket(const Aws::String& bucket_name,
    const Aws::S3::Model::BucketLocationConstraint& region = Aws::S3::Model::BucketLocationConstraint::EU)
{
    // Set up the request
    Aws::S3::Model::CreateBucketRequest request;
    request.SetBucket(bucket_name);

    // Is the region other than us-east-1 (N. Virginia)? EU??????????
    if (region != Aws::S3::Model::BucketLocationConstraint::EU)
    {
        // Specify the region as a location constraint
        Aws::S3::Model::CreateBucketConfiguration bucket_config;
        bucket_config.SetLocationConstraint(region);
        request.SetCreateBucketConfiguration(bucket_config);
    }

    // Create the bucket
    Aws::S3::S3Client s3_client;
    auto outcome = s3_client.CreateBucket(request);
    if (!outcome.IsSuccess())
    {
        auto err = outcome.GetError();
        std::cout << "ERROR: CreateBucket: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        return false;
    }

    ListBucket();

    DeleteBucket();


    return true;
}

